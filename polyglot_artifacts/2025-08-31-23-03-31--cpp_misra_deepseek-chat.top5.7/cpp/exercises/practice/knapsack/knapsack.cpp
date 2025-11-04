#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    // Handle case when maximum_weight is 0
    if (maximum_weight < 0)
    {
        return 0;
    }
    
    std::vector<std::int32_t> dp(maximum_weight + 1, 0);
    
    for (const auto& item : items)
    {
        // Handle items with weight 0 by always adding their value
        if (item.weight == 0)
        {
            if (item.value > 0)
            {
                // Since weight is 0, we can add its value to all capacities
                for (std::int32_t w = 0; w <= maximum_weight; ++w)
                {
                    dp[w] += item.value;
                }
            }
            continue;
        }
        
        // Process items with weight > 0
        for (std::int32_t w = maximum_weight; w >= item.weight; --w)
        {
            if ((dp[w - item.weight] + item.value) > dp[w])
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // The maximum value will be at dp[maximum_weight], but to be safe, find the max in case of weight 0 items
    // Since all values are positive, and we're always adding items with weight 0, dp[maximum_weight] should be the maximum
    // But to be generic, we'll find the maximum
    return *std::max_element(dp.begin(), dp.end());
}

} // namespace knapsack

