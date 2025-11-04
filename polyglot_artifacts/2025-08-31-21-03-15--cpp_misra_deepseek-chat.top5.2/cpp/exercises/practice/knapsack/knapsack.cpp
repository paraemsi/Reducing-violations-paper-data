#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    if ((maximumWeight < 0) || (items.empty()))
    {
        return 0;
    }
    if (maximumWeight == 0)
    {
        return 0;
    }
    
    // Create a DP array where dp[w] stores the maximum value for weight w
    // Since maximumWeight is >= 0, the cast is safe
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximumWeight) + 1, 0);
    
    for (const auto& item : items)
    {
        // Ensure item weight is non-negative
        // To avoid reusing the same item, we process from the end
        for (std::int32_t w = maximumWeight; w >= item.weight; --w)
        {
            // Ensure we don't access out of bounds
            // item.weight is always >= 0, so w - item.weight is valid
            std::int32_t new_value = dp[static_cast<std::size_t>(w) - static_cast<std::size_t>(item.weight)] + item.value;
            if (dp[static_cast<std::size_t>(w)] < new_value)
            {
                dp[static_cast<std::size_t>(w)] = new_value;
            }
        }
    }
    
    // The maximum value will be at dp[maximumWeight]
    return dp[static_cast<std::size_t>(maximumWeight)];
}

} // namespace knapsack

