#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    if (items.empty() || (maximumWeight <= 0))
    {
        return 0;
    }

    // Create a DP table where dp[w] represents the maximum value achievable with weight up to w
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items)
    {
        // To avoid reusing the same item, process from the end to the beginning
        for (std::int32_t w = maximumWeight; w >= 0; w--)
        {
            if (item.weight <= w)
            {
                if ((dp[w - item.weight] + item.value) > dp[w])
                {
                    dp[w] = dp[w - item.weight] + item.value;
                }
            }
        }
    }
    
    // Find the maximum value which will be at dp[maximumWeight]
    // Since all values are non-negative, and we can't exceed maximumWeight, the maximum is at the end
    return dp[maximumWeight];
}

} // namespace knapsack

