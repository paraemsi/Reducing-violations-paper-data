#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    // Handle cases where maximum weight is negative
    if (maximum_weight < 0)
    {
        return 0;
    }
    
    // Create a DP array where dp[w] stores the maximum value achievable with weight up to w
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximum_weight) + 1, 0);
    
    for (const auto& item : items)
    {
        // Ensure item weight is non-negative
        // Process from the end to avoid reusing the same item
        for (std::int32_t w = maximum_weight; w >= 0; --w)
        {
            if (item.weight <= w)
            {
                if (dp[static_cast<std::size_t>(w)] < (dp[static_cast<std::size_t>(w - item.weight)] + item.value))
                {
                    dp[static_cast<std::size_t>(w)] = dp[static_cast<std::size_t>(w - item.weight)] + item.value;
                }
            }
        }
    }
    
    // The maximum value will be at dp[maximum_weight]
    // Since all values are positive, the maximum is always at the maximum weight we can reach
    return dp[static_cast<std::size_t>(maximum_weight)];
}

} // namespace knapsack

