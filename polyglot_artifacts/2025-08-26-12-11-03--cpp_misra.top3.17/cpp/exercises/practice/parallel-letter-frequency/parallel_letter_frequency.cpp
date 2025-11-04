#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>

namespace parallel_letter_frequency {

namespace {
    // Helper: process a range of texts and accumulate letter counts
    void count_letters(const std::vector<std::string>& texts,
                       std::size_t start,
                       std::size_t end,
                       letter_frequency_map& local_map)
    {
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
    }
}

letter_frequency_map frequency(const std::vector<std::string>& texts)
{
    // Determine number of threads to use
    const std::size_t num_threads = (std::thread::hardware_concurrency() > 0U) ? std::thread::hardware_concurrency() : 2U;
    const std::size_t num_texts = texts.size();
    std::vector<std::thread> threads;
    std::vector<letter_frequency_map> local_maps(num_threads);

    // Partition the work
    std::size_t block_size = (num_texts + num_threads - 1U) / num_threads;

    for(std::size_t t = 0U; t < num_threads; ++t)
    {
        std::size_t start = t * block_size;
        std::size_t end = std::min((start + block_size), num_texts);
        threads.emplace_back(count_letters, std::cref(texts), start, end, std::ref(local_maps[t]));
    }

    for(std::thread& th : threads)
    {
        th.join();
    }

    // Merge results
    letter_frequency_map result;
    for(const auto& local : local_maps)
    {
        for(const auto& pair : local)
        {
            result[pair.first] += pair.second;
        }
    }

    return result;
}

}
