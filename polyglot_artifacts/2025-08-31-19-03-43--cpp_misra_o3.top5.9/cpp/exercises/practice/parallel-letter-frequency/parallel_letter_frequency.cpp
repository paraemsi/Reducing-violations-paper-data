#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <future>
#include <thread>
#include <string_view>

namespace {

/* Count letters in the provided sub-range of the input container.
 * The indices are half-open [first, last).
 */
[[nodiscard]] auto count_range(const std::vector<std::string_view>& texts,
                               std::size_t                         first,
                               std::size_t                         last)
    -> std::map<char, std::uint32_t>
{
    std::map<char, std::uint32_t> local_result {};

    for(std::size_t idx { first }; idx < last; ++idx)
    {
        const std::string_view text_ref { texts.at(idx) };

        for(const char ch : text_ref)
        {
            /* Convert to unsigned value for locale-independent behaviour. */
            const int ch_int {
                std::char_traits<char>::to_int_type(ch)
            };

            if(std::isalpha(ch_int) != 0)
            {
                const int lower_int { std::tolower(ch_int) };
                const char lower_ch {
                    std::char_traits<char>::to_char_type(lower_int)
                };

                ++(local_result[lower_ch]);
            }
            else
            {
                /* Non-alphabetic – ignore */ ;
            }
        }
    }

    return local_result;
}

}   // unnamed namespace

namespace parallel_letter_frequency {

[[nodiscard]] auto frequency(const std::vector<std::string_view>& texts,
                             std::uint32_t                       max_workers) -> std::map<char, std::uint32_t>
{
    const std::size_t text_count { texts.size() };

    if(text_count == 0U)
    {
        return {};
    }

    const std::uint32_t hardware_threads {
        static_cast<std::uint32_t>(std::thread::hardware_concurrency())
    };

    const std::uint32_t workers_requested { (max_workers == 0U)
                                                ? hardware_threads
                                                : max_workers };

    /* At least one worker, but never more than there are tasks. */
    const std::uint32_t worker_count {
        (workers_requested == 0U)
            ? 1U
            : static_cast<std::uint32_t>(std::min<std::size_t>(text_count,
                                                               static_cast<std::size_t>(workers_requested)))
    };

    const std::size_t chunk_size {
        (text_count + static_cast<std::size_t>(worker_count) - 1U)
            / static_cast<std::size_t>(worker_count)
    };

    std::vector<std::future<std::map<char, std::uint32_t>>> futures {};
    futures.reserve(static_cast<std::size_t>(worker_count));

    for(std::uint32_t w { 0U }; w < worker_count; ++w)
    {
        const std::size_t first { static_cast<std::size_t>(w) * chunk_size };
        const std::size_t last  {
            std::min(text_count, first + chunk_size)
        };

        futures.emplace_back(std::async(std::launch::async,
                                        count_range,
                                        std::cref(texts),
                                        first,
                                        last));
    }

    std::map<char, std::uint32_t> result {};

    for(auto& fut : futures)
    {
        const std::map<char, std::uint32_t> partial { fut.get() };

        for(const auto& [key, value] : partial)
        {
            result[key] += value;
        }
    }

    return result;
}

}   // namespace parallel_letter_frequency
