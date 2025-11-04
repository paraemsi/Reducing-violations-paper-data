#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    if ((maximum_weight <= 0) || (items.empty()))
    {
        return 0;
    }
    
    // Create a DP array where dp[i] is the maximum value with weight i
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximum_weight) + 1, 0);
    
    for (const auto& item : items)
    {
        // To avoid reusing the same item, process from the end
        // Make sure to use the correct type for the loop variable
        for (std::int32_t w = maximum_weight; w >= 0; --w)
        {
            if (item.weight <= w)
            {
                const std::int32_t candidate = dp[static_cast<std::size_t>(w - item.weight)] + item.value;
                if (candidate > dp[static_cast<std::size_t>(w)])
                {
                    dp[static_cast<std::size_t>(w)] = candidate;
                }
            }
        }
    }
    
    // Find the maximum value in the dp array
    std::int32_t max_value = 0;
    for (std::int32_t w = 0; w <= maximum_weight; ++w)
    {
        if (dp[static_cast<std::size_t>(w)] > max_value)
        {
            max_value = dp[static_cast<std::size_t>(w)];
        }
    }
    return max_value;
}

} // namespace knapsack

