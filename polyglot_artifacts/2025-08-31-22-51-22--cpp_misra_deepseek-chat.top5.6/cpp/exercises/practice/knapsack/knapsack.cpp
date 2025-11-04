#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    // Handle case where maximumWeight is 0 or items are empty
    if ((maximumWeight == 0) || (items.empty()))
    {
        return 0;
    }
    
    // Create a DP array where dp[i] is the maximum value for weight i
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximumWeight) + 1, 0);
    
    for (const auto& item : items)
    {
        // To avoid reusing the same item, process weights in reverse
        // Start from maximumWeight down to item's weight
        for (std::int32_t w = maximumWeight; w >= item.weight; --w)
        {
            // Calculate potential new value
            std::int32_t newValue = (dp[static_cast<std::size_t>(w - item.weight)]) + (item.value);
            if ((dp[static_cast<std::size_t>(w)]) < newValue)
            {
                dp[static_cast<std::size_t>(w)] = newValue;
            }
        }
    }
    
    // The maximum value will be the maximum in the dp array
    // Since all values are non-negative, and we're always filling up to maximumWeight
    std::int32_t maxValue = 0;
    for (std::int32_t w = 0; w <= maximumWeight; ++w)
    {
        if ((dp[static_cast<std::size_t>(w)]) > maxValue)
        {
            maxValue = dp[static_cast<std::size_t>(w)];
        }
    }
    
    return maxValue;
}

} // namespace knapsack

