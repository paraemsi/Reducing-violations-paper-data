#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    // Handle case when maximum_weight is 0 - we can only take items with weight 0
    std::vector<std::int32_t> dp(maximum_weight + 1, 0);
    
    for (const auto& item : items)
    {
        if (item.weight == 0)
        {
            // Add value to all dp entries since weight is 0
            for (std::int32_t w = 0; w <= maximum_weight; ++w)
            {
                dp[w] += item.value;
            }
        }
        else
        {
            // Process in reverse to avoid reusing the same item
            for (std::int32_t w = maximum_weight; w >= item.weight; --w)
            {
                if (dp[w] < (dp[w - item.weight] + item.value))
                {
                    dp[w] = dp[w - item.weight] + item.value;
                }
            }
        }
    }
    
    // Find the maximum value in dp array
    // Since all values are positive, and we can always take items with weight 0,
    // the maximum should be at the highest index, but to be safe, we'll find max
    std::int32_t max_value = 0;
    for (std::int32_t w = 0; w <= maximum_weight; ++w)
    {
        if (dp[w] > max_value)
        {
            max_value = dp[w];
        }
    }
    return max_value;
}

} // namespace knapsack

