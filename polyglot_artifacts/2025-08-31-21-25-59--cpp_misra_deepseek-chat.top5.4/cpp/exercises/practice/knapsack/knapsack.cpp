#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    // Handle negative maximum weight by treating it as 0
    if (maximumWeight < 0)
    {
        maximumWeight = 0;
    }
    
    if (items.empty())
    {
        return 0;
    }
    
    // Handle maximumWeight being 0 - only items with weight 0 can be taken
    // Since all values are positive, we want to sum their values
    if (maximumWeight == 0)
    {
        std::int32_t totalValue = 0;
        for (const auto& item : items)
        {
            if (item.weight == 0)
            {
                totalValue += item.value;
            }
        }
        return totalValue;
    }
    
    // Create a DP array where dp[w] stores the maximum value achievable with weight w
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximumWeight) + 1, 0);
    
    for (const auto& item : items)
    {
        // Skip items that are heavier than the maximum weight (but process them if weight is 0)
        if (item.weight > maximumWeight)
        {
            continue;
        }
        
        // To avoid reusing the same item, process from the end
        // For items with weight 0, they can always be added, but we need to handle them differently
        if (item.weight == 0)
        {
            // Add their value to all dp entries
            // Since all values are positive, we always want to include items with weight 0
            for (std::int32_t w = maximumWeight; w >= 0; --w)
            {
                dp[static_cast<std::size_t>(w)] += item.value;
            }
        }
        else
        {
            // Process normally
            for (std::int32_t w = maximumWeight; w >= item.weight; --w)
            {
                std::int32_t remainingWeight = w - item.weight;
                std::int32_t newValue = dp[static_cast<std::size_t>(remainingWeight)] + item.value;
                if (newValue > dp[static_cast<std::size_t>(w)])
                {
                    dp[static_cast<std::size_t>(w)] = newValue;
                }
            }
        }
    }
    
    // Find the maximum value in the dp array
    // Since all values are positive, the maximum will be at the end, but to be safe
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

