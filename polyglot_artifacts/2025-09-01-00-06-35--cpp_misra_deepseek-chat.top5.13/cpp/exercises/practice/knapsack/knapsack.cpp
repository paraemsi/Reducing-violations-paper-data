#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    if (maximumWeight < 0) 
    {
        return 0;
    }
    
    // Create a DP array where dp[w] stores maximum value for weight exactly w
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items) 
    {
        if (item.weight == 0) 
        {
            if (item.value > 0) 
            {
                // Add its value to all dp entries
                for (std::int32_t w = 0; w <= maximumWeight; ++w) 
                {
                    dp[w] += item.value;
                }
            }
        }
        else 
        {
            // To avoid reusing the same item, process weights in reverse
            for (std::int32_t w = maximumWeight; w >= item.weight; --w) 
            {
                if (dp[w] < (dp[w - item.weight] + item.value)) 
                {
                    dp[w] = dp[w - item.weight] + item.value;
                }
            }
        }
    }
    
    // The maximum value will be the maximum in the dp array
    // Since items may not fill the entire knapsack, we need to find the max up to maximumWeight
    // But in standard implementation, dp[W] is the maximum value for capacity W
    // To find the maximum value, we can simply take the last element
    // However, to be safe, we'll find the maximum in the entire array
    std::int32_t maxValue = 0;
    for (std::int32_t w = 0; w <= maximumWeight; ++w) 
    {
        if (dp[w] > maxValue) 
        {
            maxValue = dp[w];
        }
    }
    return maxValue;
}

} // namespace knapsack

