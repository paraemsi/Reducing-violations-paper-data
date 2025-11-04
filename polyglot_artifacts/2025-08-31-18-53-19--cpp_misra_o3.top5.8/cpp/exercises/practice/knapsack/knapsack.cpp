#include "knapsack.h"
#include <vector>
#include <cstddef>
#include <cstdint>

namespace knapsack
{

/*  Alias required to iterate backwards over capacity while complying with
 *  MISRA-C++ rule that forbids the direct use of std::int64_t outside an alias
 *  declaration.
 */
using diff_t = std::int64_t;

value_t maximum_value(weight_t capacity, const std::vector<Item>& items)
{
    std::vector<value_t> dp(
        static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1U),
        static_cast<value_t>(0U));

    for(const Item& item : items)
    {
        if(item.weight > capacity)
        {
            continue;
        }

        for(diff_t w = static_cast<diff_t>(capacity);
            w >= static_cast<diff_t>(item.weight);
            --w)
        {
            std::size_t const w_idx = static_cast<std::size_t>(w);
            std::size_t const prev_idx =
                static_cast<std::size_t>(
                    w - static_cast<diff_t>(item.weight));

            value_t const candidate =
                dp[prev_idx] + item.value;

            if(candidate > dp[w_idx])
            {
                dp[w_idx] = candidate;
            }
        }
    }

    return dp.back();
}

} // namespace knapsack

