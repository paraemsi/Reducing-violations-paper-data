#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    // Handle edge cases
    if ((maximumWeight <= 0) || (items.empty()))
    {
        return 0;
    }
    
    // Create a DP array to store maximum values for each weight
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximumWeight) + 1, 0);
    
    // Process each item
    for (const auto& item : items)
    {
        // Ensure the item's weight is valid
        if (item.weight < 0)
        {
            continue;
        }
        
        // Update the DP array from the end to avoid reusing items
        for (std::int32_t w = maximumWeight; w >= item.weight; --w)
        {
            std::int32_t remaining_weight = (w - item.weight);
            std::int32_t new_value = (dp[static_cast<std::size_t>(remaining_weight)] + item.value);
            if (dp[static_cast<std::size_t>(w)] < new_value)
            {
                dp[static_cast<std::size_t>(w)] = new_value;
            }
        }
    }
    
    return dp[static_cast<std::size_t>(maximumWeight)];
}

} // namespace knapsack

