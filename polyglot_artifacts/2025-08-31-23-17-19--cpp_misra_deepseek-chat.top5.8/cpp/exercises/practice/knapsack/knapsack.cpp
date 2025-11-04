#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    if (items.empty() || (maximumWeight == 0))
    {
        return 0;
    }
    
    // Create a DP table where dp[w] will store the maximum value with weight w
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items)
    {
        // To avoid reusing the same item, we process weights in reverse
        for (std::int32_t w = maximumWeight; w >= item.weight; w--)
        {
            if (dp[w] < (dp[w - item.weight] + item.value))
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // Find the maximum value in the dp array
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

