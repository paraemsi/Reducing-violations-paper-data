#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    // Handle case when maximum weight is 0
    if (maximum_weight < 0) 
    {
        return 0;
    }
    
    // Create a DP array where dp[w] stores the maximum value that can be achieved with weight at most w
    std::vector<std::int32_t> dp(maximum_weight + 1, 0);
    
    for (const auto& item : items) 
    {
        // Process from the end to avoid reusing items
        for (std::int32_t w = maximum_weight; w >= item.weight; --w) 
        {
            if (dp[w] < (dp[w - item.weight] + item.value)) 
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // Since all values are non-negative, the maximum value will be at dp[maximum_weight]
    // To find the maximum value up to maximum_weight, which is what we want
    return dp[maximum_weight];
}

} // namespace knapsack

