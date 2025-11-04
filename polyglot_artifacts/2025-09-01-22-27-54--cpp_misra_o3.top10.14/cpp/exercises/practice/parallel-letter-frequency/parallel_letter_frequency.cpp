#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cstddef>
#include <future>
#include <locale>
#include <thread>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    // Early exit: no input
    if(texts.empty())
    {
        return {};
    }

    // Determine thread count – fall back to one if detection fails
    const std::size_t hw_threads { static_cast<std::size_t>(
        (std::thread::hardware_concurrency() == 0U) ? 1U
                                                   : std::thread::hardware_concurrency()) };

    const std::size_t thread_count { (texts.size() < hw_threads) ? texts.size()
                                                                 : hw_threads };

    const std::size_t block_size { (texts.size() + thread_count - 1U) / thread_count };

    // Store futures for thread results
    std::vector<std::future<frequency_map>> futures {};
    futures.reserve(thread_count);

    const std::locale loc { "C" };

    // Launch tasks
    for(std::size_t block_index { 0U }; block_index < thread_count; ++block_index)
    {
        const std::size_t begin { block_index * block_size };
        const std::size_t end   { (begin + block_size > texts.size()) ? texts.size()
                                                                     : (begin + block_size) };

        futures.emplace_back(std::async(std::launch::async,
            [begin, end, &texts, &loc]() -> frequency_map
            {
                frequency_map local_counts {};

                for(std::size_t i { begin }; i < end; ++i)
                {
                    for(const char ch_raw : texts[i])
                    {
                        // Use locale-aware helpers – rule: no <cctype> usage
                        if(std::isalpha(static_cast<unsigned char>(ch_raw), loc))
                        {
                            const char lower_ch {
                                std::tolower(static_cast<unsigned char>(ch_raw), loc)
                            };

                            // Increment count
                            ++local_counts[lower_ch];
                        }
                    }
                }

                return local_counts;
            }));
    }

    // Merge all partial results
    frequency_map total_counts {};
    for(auto& fut : futures)
    {
        const frequency_map part { fut.get() };

        for(const auto& kv : part)
        {
            total_counts[kv.first] += kv.second;
        }
    }

    return total_counts;
}

}   // namespace parallel_letter_frequency
