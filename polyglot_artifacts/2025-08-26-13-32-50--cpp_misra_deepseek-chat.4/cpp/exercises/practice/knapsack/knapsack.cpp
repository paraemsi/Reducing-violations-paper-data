#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    // Handle cases where maximum weight is 0 or no items
    if ((maximum_weight == 0) || items.empty())
    {
        return 0;
    }
    
    // Initialize DP array with zeros
    std::vector<std::int32_t> dp(maximum_weight + 1, 0);
    
    // Process each item
    for (const auto& item : items)
    {
        // To avoid reusing the same item, process weights from maximum_weight down to item's weight
        for (std::int32_t w = maximum_weight; w >= item.weight; --w)
        {
            if (dp[w] < (dp[w - item.weight] + item.value))
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // Find the maximum value in the dp array
    // Since we want the maximum value that can be obtained with weight up to maximum_weight
    return *std::max_element(dp.begin(), dp.end());
}

} // namespace knapsack

