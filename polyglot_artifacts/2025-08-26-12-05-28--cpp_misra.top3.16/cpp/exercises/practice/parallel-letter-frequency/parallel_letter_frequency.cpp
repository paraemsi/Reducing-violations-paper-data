#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>

namespace parallel_letter_frequency {

letter_frequency_map frequency(const std::vector<std::string>& texts)
{
    return letter_frequency(texts);
}

namespace {
    // Helper: process a range of texts and accumulate letter counts
    void count_letters(const std::vector<std::string>& texts,
                       std::size_t start,
                       std::size_t end,
                       letter_frequency_map& local_result)
    {
        for(std::size_t i = start; i < end; ++i)
        {
            for(char ch : texts[i])
            {
                if(std::isalpha(static_cast<unsigned char>(ch)))
                {
                    char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                    ++local_result[lower];
                }
            }
        }
    }
}

letter_frequency_map letter_frequency(const std::vector<std::string>& texts)
{
    letter_frequency_map result;

    if(texts.empty())
    {
        return result;
    }

    // Determine number of threads to use
    const std::size_t hardware_threads = (std::thread::hardware_concurrency() != 0U)
        ? static_cast<std::size_t>(std::thread::hardware_concurrency())
        : 2U;

    const std::size_t num_threads = (hardware_threads < texts.size()) ? hardware_threads : texts.size();
    std::vector<std::thread> threads;
    std::vector<letter_frequency_map> local_results(num_threads);

    const std::size_t block_size = texts.size() / num_threads;
    const std::size_t remainder = texts.size() % num_threads;

    std::size_t block_start = 0U;

    for(std::size_t t = 0U; t < num_threads; ++t)
    {
        std::size_t block_end = block_start + block_size + ((t < remainder) ? 1U : 0U);

        threads.emplace_back(
            count_letters,
            std::cref(texts),
            block_start,
            block_end,
            std::ref(local_results[t])
        );

        block_start = block_end;
    }

    for(std::thread& th : threads)
    {
        if(th.joinable())
        {
            th.join();
        }
    }

    // Merge local results
    for(const auto& local : local_results)
    {
        for(const auto& pair : local)
        {
            result[pair.first] += pair.second;
        }
    }

    return result;
}

}
