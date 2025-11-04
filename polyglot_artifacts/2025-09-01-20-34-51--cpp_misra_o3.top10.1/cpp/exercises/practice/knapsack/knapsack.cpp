#include "knapsack.h"

#include <algorithm>
#include <cstdint>
#include <vector>

namespace knapsack
{

auto maximum_value(weight_t                 capacity,
                   const std::vector<Item>& items) -> value_t
{
    /* Dynamic-programming array where dp[w] holds the best value reachable
       with exact weight w. */
    std::vector<value_t> dp(
        static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1U),
        static_cast<value_t>(0U));

    for (const auto& item : items)
    {
        /* Skip items that are heavier than the current knapsack capacity. */
        if (item.weight > capacity)
        {
            continue;
        }

        /* Traverse weights in descending order to respect the 0-1 constraint. */
        for (weight_t w = capacity; (w >= item.weight); --w)
        {
            const value_t prev =
                dp[static_cast<std::size_t>(w - item.weight)];
            const value_t candidate =
                static_cast<value_t>(prev + item.value);

            if (candidate > dp[static_cast<std::size_t>(w)])
            {
                dp[static_cast<std::size_t>(w)] = candidate;
            }
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

