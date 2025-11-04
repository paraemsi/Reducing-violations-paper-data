#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts)
{
    frequency_map result{};

    if ((texts.empty()))
    {
        return result;
    }

    const std::size_t hw = static_cast<std::size_t>(std::thread::hardware_concurrency());
    const std::size_t max_threads = ((hw != static_cast<std::size_t>(0U)) ? hw : static_cast<std::size_t>(2U));
    const std::size_t thread_count = std::min<std::size_t>(max_threads, texts.size());

    std::vector<frequency_map> partials(thread_count);
    std::vector<std::thread> workers{};
    workers.reserve(thread_count);

    const std::size_t block_size =
        ((texts.size() + (thread_count - static_cast<std::size_t>(1U))) / thread_count);

    for (std::size_t t = static_cast<std::size_t>(0U); (t < thread_count); ++t)
    {
        const std::size_t start = (t * block_size);
        const std::size_t end = std::min<std::size_t>(texts.size(), (start + block_size));

        workers.emplace_back([start, end, &texts, &partials, t]() {
            frequency_map local{};

            for (std::size_t i = start; (i < end); ++i)
            {
                const std::string_view s = texts[i];

                for (const char ch : s)
                {
                    // Convert to int representation using char_traits per MISRA guidance.
                    const auto ich = std::char_traits<char>::to_int_type(ch);

                    if ((std::isalpha(ich) != 0))
                    {
                        const char lower = std::char_traits<char>::to_char_type(std::tolower(ich));
                        ++local[lower];
                    }
                    else
                    {
                        // Not an alphabetic character: ignore.
                    }
                }
            }

            partials[t] = std::move(local);
        });
    }

    for (std::thread& th : workers)
    {
        if (th.joinable())
        {
            th.join();
        }
        else
        {
            // No-op
        }
    }

    for (const frequency_map& part : partials)
    {
        for (const auto& kv : part)
        {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

}
