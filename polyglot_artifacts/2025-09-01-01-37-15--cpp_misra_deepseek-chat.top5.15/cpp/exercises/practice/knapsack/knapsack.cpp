#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    if (items.empty()) 
    {
        return 0;
    }
    
    // Handle case where maximumWeight is 0
    if (maximumWeight == 0)
    {
        return 0;
    }
    
    // Create a DP array where dp[w] stores the maximum value for weight up to w
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximumWeight) + 1, 0);
    
    for (const auto& item : items)
    {
        // To avoid reusing the same item, we process from the end
        for (std::int32_t w = maximumWeight; w >= item.weight; --w)
        {
            std::int32_t const newValue = (dp[static_cast<std::size_t>(w) - static_cast<std::size_t>(item.weight)] + item.value);
            if (dp[static_cast<std::size_t>(w)] < newValue)
            {
                dp[static_cast<std::size_t>(w)] = newValue;
            }
        }
    }
    
    // Find the maximum value in the dp array
    // Since values can be non-decreasing, we need to find the maximum
    std::int32_t maxValue = 0;
    for (std::int32_t w = 0; w <= maximumWeight; ++w)
    {
        if (dp[static_cast<std::size_t>(w)] > maxValue)
        {
            maxValue = dp[static_cast<std::size_t>(w)];
        }
    }
    return maxValue;
}

} // namespace knapsack

