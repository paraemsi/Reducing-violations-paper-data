#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <future>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map_t
{
    frequency_map_t result {};

    /* Launch asynchronous tasks – one per input string */
    std::vector<std::future<frequency_map_t>> tasks {};
    tasks.reserve(texts.size());

    for(const std::string_view text : texts)
    {
        tasks.emplace_back
        (
            std::async(std::launch::async, [text]() -> frequency_map_t
            {
                frequency_map_t local_counts {};

                for(char ch : text)
                {
                    /* Classify and normalise character – avoid direct numeric use */
                    const int ch_int { std::char_traits<char>::to_int_type(ch) };

                    if((std::isalpha(ch_int)) != 0)
                    {
                        const int  lower_int { std::tolower(ch_int) };
                        const char lower_ch  { std::char_traits<char>::to_char_type(lower_int) };

                        ++local_counts[lower_ch];
                    }
                }

                return local_counts;
            })
        );
    }

    /* Merge partial results */
    for(std::future<frequency_map_t>& fut : tasks)
    {
        const frequency_map_t local { fut.get() };

        for(const auto& kv : local)
        {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

} /* namespace parallel_letter_frequency */
