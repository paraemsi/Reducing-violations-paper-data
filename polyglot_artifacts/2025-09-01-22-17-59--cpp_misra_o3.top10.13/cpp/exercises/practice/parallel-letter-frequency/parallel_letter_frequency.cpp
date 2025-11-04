#include "parallel_letter_frequency.h"

#include <algorithm>
#include <execution>
#include <locale>
#include <numeric>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string>& texts) -> std::unordered_map<char, count_t>
{
    const std::locale loc {};
    const std::size_t input_size {texts.size()};

    /*  Each input string gets its own local map that is filled in parallel.
        After the parallel phase the partial results are merged sequentially. */
    std::vector<std::unordered_map<char, count_t>> partial_results(input_size);

    std::vector<std::size_t> indices(input_size);
    std::iota(indices.begin(), indices.end(), static_cast<std::size_t>(0U));

    std::for_each(
        std::execution::par,
        indices.begin(),
        indices.end(),
        [&](std::size_t idx)
        {
            const std::string& current_text {texts[idx]};
            std::unordered_map<char, count_t>& local_result {partial_results[idx]};

            for (const char ch : current_text)
            {
                /*  Use locale-aware helpers; only equality/inequality on
                    character values is permitted by the MISRA rule set. */
                if (std::isalpha(ch, loc) != 0)
                {
                    const char lowered {static_cast<char>(std::tolower(ch, loc))};
                    (void)local_result[lowered]++;            /* increment counter   */
                }
            }
        });

    /*  Aggregate the per-thread maps into one final map. */
    std::unordered_map<char, count_t> aggregated {};

    for (const auto& partial : partial_results)
    {
        for (const auto& kv : partial)
        {
            (void)aggregated[kv.first] += kv.second;
        }
    }

    return aggregated;
}

/*  Overload accepting a vector of string_view so that the public API
    matches the Exercism test-suite expectations without duplicating
    the algorithmic code. */
auto frequency(const std::vector<std::string_view>& texts) -> std::unordered_map<char, count_t>
{
    std::vector<std::string> owned {};
    owned.reserve(texts.size());

    for (const std::string_view sv : texts)
    {
        owned.emplace_back(sv);
    }

    /*  Delegate the processing to the std::string overload. */
    return frequency(owned);
}

} // namespace parallel_letter_frequency
