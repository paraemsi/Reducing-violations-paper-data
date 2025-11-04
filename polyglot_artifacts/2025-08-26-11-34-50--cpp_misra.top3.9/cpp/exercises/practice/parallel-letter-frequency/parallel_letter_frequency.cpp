#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
#include <map>
#include <cstdint>

namespace parallel_letter_frequency {

namespace {
    // Helper: count letters in a range of strings
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
                if((std::isalpha(static_cast<unsigned char>(ch))) != 0)
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

    const std::size_t num_texts = texts.size();
    const std::size_t num_threads = (std::thread::hardware_concurrency() > 0U) ? std::thread::hardware_concurrency() : 2U;
    const std::size_t chunk_size = (num_texts + num_threads - 1U) / num_threads;

    std::vector<std::thread> threads;

    for(std::size_t t = 0U; t < num_threads; ++t)
    {
        std::size_t start = t * chunk_size;
        std::size_t end = (start + chunk_size < num_texts) ? (start + chunk_size) : num_texts;
        if(start >= end)
        {
            break;
        }
        threads.emplace_back(count_letters, std::cref(texts), start, end, std::ref(freq_map), std::ref(map_mutex));
    }

    for(auto& th : threads)
    {
        th.join();
    }

    return freq_map;
}

}
