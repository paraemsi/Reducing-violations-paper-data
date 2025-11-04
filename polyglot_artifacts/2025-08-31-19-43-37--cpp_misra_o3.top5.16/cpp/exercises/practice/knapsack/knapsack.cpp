#include "knapsack.h"

#include <cstddef>     // for std::size_t
#include <vector>      // for std::vector
#include <cstdint>     // for fixed-width integer types

namespace knapsack
{

value_t maximum_value(weight_t capacity, const std::vector<Item>& items)
{
    /* Dynamic-programming table: dp[w] is the best value achievable
     * with total weight exactly w.
     */
    std::vector<value_t> dp(static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1U),
                            static_cast<value_t>(0U));

    for(const Item& item : items)
    {
        /* Iterate weights in descending order to ensure each item is
         * considered only once (0-1 knapsack).
         */
        for(std::int64_t w_idx = static_cast<std::int64_t>(capacity);
            w_idx >= static_cast<std::int64_t>(item.weight);
            --w_idx)
        {
            const weight_t w = static_cast<weight_t>(w_idx);

            const value_t candidate =
                static_cast<value_t>(dp[static_cast<std::size_t>(w - item.weight)] + item.value);

            if(candidate > dp[static_cast<std::size_t>(w)])
            {
                dp[static_cast<std::size_t>(w)] = candidate;
            }
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

