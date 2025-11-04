#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    if (maximumWeight < 0)
    {
        return 0;
    }
    
    // Handle case where maximumWeight is 0
    if (maximumWeight == 0)
    {
        // Check if any item has weight 0, take maximum value among them
        // But according to the problem, all values are strictly positive, and weights?
        // The problem says Bob can take only one of each item, and all values are strictly positive
        // But if weight is 0, we can take them without affecting the total weight
        // However, the maximum weight is 0, so we can only take items with weight 0
        std::int32_t maxValue = 0;
        for (const auto& item : items)
        {
            if ((item.weight == 0) && (item.value > maxValue))
            {
                maxValue = item.value;
            }
        }
        return maxValue;
    }
    
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items)
    {
        // Process in reverse to avoid reusing items
        for (std::int32_t w = maximumWeight; w >= item.weight; --w)
        {
            // Ensure we don't access negative indices
            if (item.weight <= w)
            {
                std::int32_t newValue = dp[w - item.weight] + item.value;
                if (dp[w] < newValue)
                {
                    dp[w] = newValue;
                }
            }
        }
    }
    
    // Find the maximum value which will be at dp[maximumWeight]
    // But to be safe, let's find the maximum in the entire array
    std::int32_t maxValue = 0;
    for (std::int32_t w = 0; w <= maximumWeight; ++w)
    {
        if (dp[w] > maxValue)
        {
            maxValue = dp[w];
        }
    }
    return maxValue;
}

} // namespace knapsack

