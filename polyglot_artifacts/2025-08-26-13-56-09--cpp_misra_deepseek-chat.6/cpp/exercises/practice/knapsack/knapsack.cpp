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
    
    // Handle case where maximumWeight is 0 - we can only take items with weight 0
    // Since all values are positive, their sum will be the maximum value
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items)
    {
        // Skip items that are heavier than the maximum weight to prevent negative indices
        if (item.weight > maximumWeight)
        {
            continue;
        }
        // Process from the end to avoid reusing the same item multiple times
        for (std::int32_t w = maximumWeight; w >= item.weight; w--)
        {
            if (dp[w] < (dp[w - item.weight] + item.value))
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // The maximum value might not be at dp[maximumWeight] if all items have weight 0
    // So find the maximum in the entire dp array
    // Since all values are positive, and we can always include items with weight 0, 
    // the maximum value will be at some index
    std::int32_t maxValue = 0;
    for (std::int32_t w = 0; w <= maximumWeight; w++)
    {
        if (dp[w] > maxValue)
        {
            maxValue = dp[w];
        }
    }
    return maxValue;
}

} // namespace knapsack

