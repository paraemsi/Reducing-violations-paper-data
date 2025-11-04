#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <future>
#include <functional>   // std::cref
#include <string>
#include <string_view>
#include <thread>

namespace parallel_letter_frequency {

/*  Helper – count letters inside a sub-range of the input texts                 */
static auto count_subrange(const std::vector<std::string_view>& texts,
                           std::size_t                          first,
                           std::size_t                          last) -> frequency_map
{
    frequency_map local_counts{};

    for(std::size_t idx{first}; idx < last; ++idx)
    {
        for(char ch : texts[idx])
        {
            auto const code{ std::char_traits<char>::to_int_type(ch) };

            if((std::isalpha(code)) != 0)
            {
                char const lower{ std::char_traits<char>::to_char_type(
                    std::tolower(code)) };

                /* Equality comparison of characters is allowed                   */
                local_counts[lower] += static_cast<std::uint32_t>(1U);
            }
        }
    }
    return local_counts;
}

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    frequency_map result{};

    if(texts.empty())
    {
        return result;
    }

    /*  Determine a reasonable thread count                                      */
    std::size_t const hardware_threads{static_cast<std::size_t>(
        (std::thread::hardware_concurrency() != 0U) ?
            std::thread::hardware_concurrency() : 2U)};

    std::size_t const thread_count{
        std::min<std::size_t>(hardware_threads, texts.size())};

    std::vector<std::future<frequency_map>> tasks{};
    tasks.reserve(thread_count);

    /*  Launch tasks that work on disjoint slices                                */
    for(std::size_t t{0U}; t < thread_count; ++t)
    {
        std::size_t const first{(t * texts.size()) / thread_count};
        std::size_t const last {((t + 1U) * texts.size()) / thread_count};

        tasks.emplace_back(std::async(std::launch::async,
                                      count_subrange,
                                      std::cref(texts),
                                      first,
                                      last));
    }

    /*  Merge all partial maps into the final result                             */
    for(auto& fut : tasks)
    {
        frequency_map const partial{fut.get()};
        for(auto const& element : partial)
        {
            result[element.first] += element.second;
        }
    }

    return result;
}

auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    std::vector<std::string_view> views{};
    views.reserve(texts.size());

    for(const std::string& str : texts)
    {
        views.emplace_back(str);
    }

    return frequency(views);
}

} // namespace parallel_letter_frequency
