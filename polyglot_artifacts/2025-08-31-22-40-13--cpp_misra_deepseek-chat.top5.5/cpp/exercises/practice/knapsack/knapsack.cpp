#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    if ((maximum_weight == 0) || (items.empty())) 
    {
        return 0;
    }
    
    // Create a DP array where dp[w] stores the maximum value for weight w
    std::vector<std::int32_t> dp(maximum_weight + 1, 0);
    
    for (const auto& item : items) 
    {
        // To avoid reusing the same item, process weights in reverse
        for (std::int32_t w = maximum_weight; w >= 0; --w) 
        {
            if (w >= item.weight) 
            {
                if (dp[w] < (dp[w - item.weight] + item.value)) 
                {
                    dp[w] = dp[w - item.weight] + item.value;
                }
            }
        }
    }
    
    // The maximum value will be at dp[maximum_weight]
    // But to be safe, we can find the maximum in the entire array
    // However, since all values are non-negative, and we're always adding, dp is non-decreasing
    return dp[maximum_weight];
}

} // namespace knapsack

