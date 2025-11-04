#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    // Handle cases where maximum weight is non-positive or items list is empty
    if ((maximumWeight <= 0) || (items.empty()))
    {
        return 0;
    }
    
    // Create a DP array where dp[i] = maximum value with weight i
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximumWeight) + 1, 0);
    
    for (const auto& item : items)
    {
        // Process from the end to avoid reusing the same item multiple times
        for (std::int32_t w = maximumWeight; w >= item.weight; --w)
        {
            std::int32_t remaining_weight = (w - item.weight);
            // Ensure we don't have negative index
            if (remaining_weight >= 0)
            {
                std::int32_t new_value = (dp[static_cast<std::size_t>(remaining_weight)] + item.value);
                if ((dp[static_cast<std::size_t>(w)] < new_value))
                {
                    dp[static_cast<std::size_t>(w)] = new_value;
                }
            }
        }
    }
    
    // Find the maximum value in the dp array
    std::int32_t maxValue = 0;
    for (std::int32_t w = 0; w <= maximumWeight; ++w)
    {
        if ((dp[static_cast<std::size_t>(w)] > maxValue))
        {
            maxValue = dp[static_cast<std::size_t>(w)];
        }
    }
    return maxValue;
}

} // namespace knapsack

