#include "parallel_letter_frequency.h"

#include <algorithm>
#include <future>
#include <locale>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <cstddef>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts)
    -> frequency_map
{
    const std::locale loc {};
    frequency_map result {};

    if(texts.empty())
    {
        return result;
    }

    const std::size_t hw_threads { (static_cast<std::size_t>(std::thread::hardware_concurrency()) == 0U)
                                       ? 1U
                                       : static_cast<std::size_t>(std::thread::hardware_concurrency()) };

    const std::size_t worker_count { (texts.size() < hw_threads) ? texts.size() : hw_threads };
    const std::size_t block_size { (texts.size() + worker_count - 1U) / worker_count };

    std::vector<std::future<std::unordered_map<char, letter_count_t>>> futures {};
    futures.reserve(worker_count);

    for(std::size_t i { 0U }; i < worker_count; ++i)
    {
        const std::size_t begin_index { i * block_size };
        if(begin_index >= texts.size())
        {
            break;
        }

        const std::size_t end_index
        {
            ( (i + 1U) * block_size < texts.size() )
                ? ( (i + 1U) * block_size )
                : texts.size()
        };

        futures.emplace_back(std::async(std::launch::async,
            [begin_index, end_index, &texts, &loc]() -> std::unordered_map<char, letter_count_t>
            {
                std::unordered_map<char, letter_count_t> local_counts {};

                for(std::size_t j { begin_index }; j < end_index; ++j)
                {
                    for(const char ch : texts[j])
                    {
                        if((std::isalpha(ch, loc)) != 0)
                        {
                            const char lower_ch { std::tolower(ch, loc) };
                            ++local_counts[lower_ch];
                        }
                    }
                }

                return local_counts;
            }));
    }

    for(auto& fut : futures)
    {
        const std::unordered_map<char, letter_count_t> local_map { fut.get() };
        for(const auto& kv : local_map)
        {
            const char key { kv.first };
            const letter_count_t value { kv.second };
            result[key] += value;
        }
    }

    return result;
}

}   // namespace parallel_letter_frequency
