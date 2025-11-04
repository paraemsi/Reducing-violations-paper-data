#include "parallel_letter_frequency.h"

#include <algorithm>
#include <future>
#include <iterator>
#include <locale>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

namespace parallel_letter_frequency {

namespace {


}  // namespace


auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    const std::size_t total_texts { texts.size() };
    if(total_texts == static_cast<std::size_t>(0U))
    {
        return {};
    }

    const unsigned int hw_raw { std::thread::hardware_concurrency() };
    const std::size_t hw_threads { (hw_raw != 0U) ? static_cast<std::size_t>(hw_raw)
                                                  : static_cast<std::size_t>(2U) };

    const std::size_t task_count { (total_texts < hw_threads) ? total_texts : hw_threads };
    const std::size_t block_size { (total_texts + task_count - static_cast<std::size_t>(1U)) / task_count };

    const std::locale loc {};

    std::vector<std::future<frequency_map>> futures {};
    futures.reserve(task_count);

    auto begin_it = texts.cbegin();
    for(std::size_t i { 0U }; i < task_count; ++i)
    {
        const auto end_it = (i == (task_count - static_cast<std::size_t>(1U)))
                                ? texts.cend()
                                : std::next(begin_it, static_cast<std::ptrdiff_t>(block_size));

        futures.emplace_back(std::async(
            std::launch::async,
            [](std::vector<std::string_view>::const_iterator b,
               std::vector<std::string_view>::const_iterator e,
               const std::locale&                            l) -> frequency_map
            {
                frequency_map local {};
                for(auto it = b; it != e; ++it)
                {
                    for(const char ch : *it)
                    {
                        if(std::isalpha(ch, l))
                        {
                            const char lower_ch { std::tolower(ch, l) };
                            ++local[lower_ch];
                        }
                    }
                }
                return local;
            },
            begin_it,
            end_it,
            std::cref(loc)));

        begin_it = end_it;
    }

    frequency_map total_counts {};
    for(auto& fut : futures)
    {
        const frequency_map partial { fut.get() };
        for(const auto& [letter, count] : partial)
        {
            total_counts[letter] += count;
        }
    }

    return total_counts;
}

}  // namespace parallel_letter_frequency
