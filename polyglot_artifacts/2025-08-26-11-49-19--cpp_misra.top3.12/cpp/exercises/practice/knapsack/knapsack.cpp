#include "knapsack.h"
#include <vector>
#include <cstdint>
#include <algorithm>

namespace knapsack
{

value_type maximum_value(weight_type capacity, const std::vector<Item>& items)
{
    // Use dynamic programming: dp[w] = max value for weight w
    // All arithmetic and comparisons are parenthesized per MISRA C++ rules

    const std::size_t n = items.size();
    std::vector<value_type> dp(static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1), static_cast<value_type>(0));

    for(std::size_t i = static_cast<std::size_t>(0); (i < n); ++i)
    {
        weight_type item_weight = items[i].weight;
        value_type item_value = items[i].value;

        // Go backwards to avoid using the same item more than once
        for(weight_type w = capacity; (w >= item_weight); --w)
        {
            value_type candidate = (dp[static_cast<std::size_t>(w - item_weight)] + item_value);
            if(dp[static_cast<std::size_t>(w)] < candidate)
            {
                dp[static_cast<std::size_t>(w)] = candidate;
            }
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

