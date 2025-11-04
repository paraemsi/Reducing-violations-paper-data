#include "knapsack.h"
#include <vector>
#include <cstddef> // for std::size_t
#include <algorithm> // for std::max

namespace knapsack
{

value_type maximum_value(weight_type capacity, const std::vector<Item>& items)
{
    // Defensive: treat negative capacity as zero
    if (capacity <= static_cast<weight_type>(0))
    {
        return static_cast<value_type>(0);
    }

    std::size_t n = items.size();
    // Use a 1D DP array for space efficiency
    std::vector<value_type> dp(static_cast<std::size_t>(capacity) + 1, static_cast<value_type>(0));

    for (std::size_t i = 0U; i < n; ++i)
    {
        weight_type w = items[i].weight;
        value_type v = items[i].value;
        // Only process if weight is positive and does not exceed capacity
        if ((w > static_cast<weight_type>(0)) && (w <= capacity))
        {
            // Traverse backwards to avoid using the same item more than once
            for (weight_type j = capacity; j >= w; --j)
            {
                // Parenthesize arithmetic and relational expressions per MISRA
                dp[static_cast<std::size_t>(j)] = std::max(
                    dp[static_cast<std::size_t>(j)],
                    (dp[static_cast<std::size_t>(j - w)] + v)
                );
            }
        }
    }
    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

