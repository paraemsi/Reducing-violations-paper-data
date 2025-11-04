#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    if (maximumWeight < 0)
    {
        return 0;
    }
    if (items.empty())
    {
        return 0;
    }
    
    // Handle items with weight 0 by always adding their value
    std::int32_t totalValueFromZeroWeightItems = 0;
    std::vector<Item> validItems;
    for (const auto& item : items)
    {
        if (item.weight == 0)
        {
            // Always take items with zero weight as they don't affect the capacity
            if (item.value > 0)
            {
                totalValueFromZeroWeightItems += item.value;
            }
        }
        else if (item.weight > 0 && item.weight <= maximumWeight)
        {
            validItems.push_back(item);
        }
        // Ignore items with weight > maximumWeight or negative weight (though weights should be positive per instructions)
    }
    
    // If maximumWeight is 0, we can only take zero-weight items
    if (maximumWeight == 0)
    {
        return totalValueFromZeroWeightItems;
    }
    
    // Use a 1D DP array to save space
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : validItems)
    {
        // Process from the end to avoid reusing items
        for (std::int32_t w = maximumWeight; w >= item.weight; w--)
        {
            if (dp[w - item.weight] + item.value > dp[w])
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // The maximum value is the maximum in dp plus the value from zero-weight items
    // Since we can always take all zero-weight items without affecting the knapsack's capacity
    // Find the maximum value in the dp array
    std::int32_t maxValue = 0;
    for (std::int32_t w = 0; w <= maximumWeight; w++)
    {
        if (dp[w] > maxValue)
        {
            maxValue = dp[w];
        }
    }
    
    return maxValue + totalValueFromZeroWeightItems;
}

} // namespace knapsack

