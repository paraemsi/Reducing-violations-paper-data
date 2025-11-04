#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>

namespace parallel_letter_frequency {

namespace {
    // Helper: process a range of texts and count letter frequencies
    void count_letters(const std::vector<std::string>& texts,
                       std::size_t start,
                       std::size_t end,
                       letter_frequency_map& freq_map,
                       std::mutex& map_mutex)
    {
        letter_frequency_map local_map;
        for(std::size_t i = start; i < end; ++i)
        {
            for(char ch : texts[i])
            {
                if(std::isalpha(static_cast<unsigned char>(ch)))
                {
                    char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                    ++local_map[lower];
                }
            }
        }
        // Merge local_map into shared freq_map
        std::lock_guard<std::mutex> lock(map_mutex);
        for(const auto& pair : local_map)
        {
            freq_map[pair.first] += pair.second;
        }
    }
}

letter_frequency_map frequency(const std::vector<std::string>& texts)
{
    letter_frequency_map freq_map;
    std::mutex map_mutex;

    std::size_t num_texts = texts.size();
    if(num_texts == 0U)
    {
        return freq_map;
    }

    unsigned int num_threads = std::thread::hardware_concurrency();
    if(num_threads == 0U)
    {
        num_threads = 2U;
    }
    if(num_threads > num_texts)
    {
        num_threads = static_cast<unsigned int>(num_texts);
    }

    std::vector<std::thread> threads;
    std::size_t block_size = num_texts / num_threads;
    std::size_t remainder = num_texts % num_threads;

    std::size_t start = 0U;
    for(unsigned int t = 0U; t < num_threads; ++t)
    {
        std::size_t end = start + block_size + ((t < remainder) ? 1U : 0U);
        threads.emplace_back(count_letters, std::cref(texts), start, end, std::ref(freq_map), std::ref(map_mutex));
        start = end;
    }

    for(auto& th : threads)
    {
        th.join();
    }

    return freq_map;
}

}
