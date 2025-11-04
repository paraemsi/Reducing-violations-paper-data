#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    // Handle case when maximum weight is 0
    if (maximum_weight == 0)
    {
        std::int32_t total_value = 0;
        for (const auto& item : items)
        {
            if (item.weight == 0)
            {
                total_value += item.value;
            }
        }
        return total_value;
    }
    
    // Initialize DP array
    std::vector<std::int32_t> dp(maximum_weight + 1, 0);
    
    // First, sum up values of items with weight 0
    std::int32_t zero_weight_value = 0;
    for (const auto& item : items)
    {
        if (item.weight == 0)
        {
            zero_weight_value += item.value;
        }
    }
    
    // Process items with weight > 0
    for (const auto& item : items)
    {
        // Skip items with weight 0 as they're already accounted for
        if (item.weight == 0)
        {
            continue;
        }
        // Process from the end to the beginning to avoid reusing the same item
        for (std::int32_t w = maximum_weight; w >= item.weight; --w)
        {
            if (dp[w] < (dp[w - item.weight] + item.value))
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // Add the value from zero-weight items to all dp entries
    // Since zero-weight items can always be taken, their value is always included
    // Find the maximum value in dp and add zero_weight_value
    std::int32_t max_value = 0;
    for (std::int32_t w = 0; w <= maximum_weight; ++w)
    {
        if (dp[w] > max_value)
        {
            max_value = dp[w];
        }
    }
    return max_value + zero_weight_value;
}

} // namespace knapsack

