#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    // Handle cases where maximum weight is 0 or no items
    if ((maximum_weight == 0) || (items.empty()))
    {
        return 0;
    }
    
    // Create a DP array where dp[i] is the maximum value with weight i
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximum_weight) + 1, 0);
    
    for (const auto& item : items)
    {
        // To avoid reusing the same item, we process from the end
        // Ensure we use the same type for the loop counter
        for (std::int32_t i = maximum_weight; i >= item.weight; --i)
        {
            // Ensure we don't access out of bounds
            // The remaining weight is always non-negative because i >= item.weight
            std::int32_t remaining_weight = i - item.weight;
            std::int32_t new_value = dp[static_cast<std::size_t>(remaining_weight)] + item.value;
            if (dp[static_cast<std::size_t>(i)] < new_value)
            {
                dp[static_cast<std::size_t>(i)] = new_value;
            }
        }
    }
    
    // Find the maximum value in the dp array
    // The maximum value could be at any weight up to maximum_weight
    std::int32_t max_value = 0;
    for (std::int32_t i = 0; i <= maximum_weight; ++i)
    {
        if (dp[static_cast<std::size_t>(i)] > max_value)
        {
            max_value = dp[static_cast<std::size_t>(i)];
        }
    }
    return max_value;
}

} // namespace knapsack

