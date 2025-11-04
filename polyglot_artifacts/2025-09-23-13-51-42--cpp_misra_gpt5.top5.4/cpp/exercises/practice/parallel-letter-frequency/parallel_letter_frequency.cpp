#include "parallel_letter_frequency.h"

#include <cstddef>
#include <future>
#include <locale>
#include <map>
#include <thread>
#include <utility>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    if (texts.empty())
    {
        return frequency_map{};
    }

    const std::size_t n = texts.size();

    const std::size_t hc = static_cast<std::size_t>(std::thread::hardware_concurrency());
    const std::size_t max_threads = (hc > static_cast<std::size_t>(0U)) ? hc : static_cast<std::size_t>(1U);
    const std::size_t thread_count = (n < max_threads) ? n : max_threads;

    if (thread_count <= static_cast<std::size_t>(1U))
    {
        // Sequential fallback
        frequency_map result{};
        const std::locale loc = std::locale::classic();
        const auto& facet = std::use_facet<std::ctype<char>>(loc);

        for (const std::string_view& s : texts)
        {
            for (char ch : s)
            {
                if (facet.is(std::ctype_base::alpha, ch))
                {
                    const char lower = facet.tolower(ch);
                    ++result[lower];
                }
            }
        }

        return result;
    }

    const std::size_t block_size = ((n + (thread_count - static_cast<std::size_t>(1U))) / thread_count);

    auto count_range = [&texts](std::size_t begin, std::size_t end) -> frequency_map
    {
        frequency_map local{};
        const std::locale loc = std::locale::classic();
        const auto& facet = std::use_facet<std::ctype<char>>(loc);

        for (std::size_t i = begin; i < end; ++i)
        {
            const std::string_view& s = texts.at(i);
            for (char ch : s)
            {
                if (facet.is(std::ctype_base::alpha, ch))
                {
                    const char lower = facet.tolower(ch);
                    ++local[lower];
                }
            }
        }

        return local;
    };

    std::vector<std::future<frequency_map>> futures{};
    futures.reserve(thread_count);

    for (std::size_t block_index = static_cast<std::size_t>(0U); block_index < thread_count; ++block_index)
    {
        const std::size_t begin = (block_index * block_size);
        const std::size_t end = (((begin + block_size) < n) ? (begin + block_size) : n);
        futures.emplace_back(std::async(std::launch::async, count_range, begin, end));
    }

    frequency_map result{};

    for (auto& fut : futures)
    {
        frequency_map partial = fut.get();
        for (const auto& kv : partial)
        {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
