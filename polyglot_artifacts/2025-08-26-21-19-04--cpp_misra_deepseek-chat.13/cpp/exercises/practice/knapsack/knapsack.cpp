#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace knapsack
{

int maximum_value(int maximumWeight, const std::vector<Item>& items)
{
    // Since the input uses int, and we need to follow MISRA rules, we'll use fixed-width types internally
    // First, check if the number of items is zero or maximumWeight is non-positive
    if ((items.size() == 0U) || (maximumWeight <= 0))
    {
        return 0;
    }
    
    // Convert to fixed-width types
    const std::int32_t maxWeight = static_cast<std::int32_t>(maximumWeight);
    
    // Create DP table
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maxWeight) + 1U, 0);
    
    // Process each item
    for (std::size_t i = 0U; i < items.size(); i++)
    {
        const Item& currentItem = items[i];
        // Convert to fixed-width types
        const std::int32_t itemWeight = static_cast<std::int32_t>(currentItem.weight);
        const std::int32_t itemValue = static_cast<std::int32_t>(currentItem.value);
        
        // Update DP table in reverse
        for (std::int32_t w = maxWeight; w >= itemWeight; w--)
        {
            // Calculate remaining weight and new value
            const std::int32_t remainingWeight = (w - itemWeight);
            const std::int32_t newValue = (dp[static_cast<std::size_t>(remainingWeight)] + itemValue);
            
            // Update if the new value is greater
            if (dp[static_cast<std::size_t>(w)] < newValue)
            {
                dp[static_cast<std::size_t>(w)] = newValue;
            }
        }
    }
    
    // Find the maximum value
    std::int32_t maxValue = 0;
    for (std::size_t w = 0U; w <= static_cast<std::size_t>(maxWeight); w++)
    {
        if (dp[w] > maxValue)
        {
            maxValue = dp[w];
        }
    }
    
    return static_cast<int>(maxValue);
}

} // namespace knapsack

