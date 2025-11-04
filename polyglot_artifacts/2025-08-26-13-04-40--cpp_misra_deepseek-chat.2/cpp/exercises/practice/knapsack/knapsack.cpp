#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    if ((items.empty()) || (maximumWeight <= 0))
    {
        return 0;
    }

    // Create a DP table where dp[w] represents the maximum value that can be obtained with weight w
    // We can optimize space by using a 1D array
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items)
    {
        // Process weights in reverse to avoid reusing the same item
        for (std::int32_t w = maximumWeight; w >= item.weight; w--)
        {
            if (dp[w] < (dp[w - item.weight] + item.value))
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // The maximum value will be the maximum of all dp[w]
    // Since all values are positive, it's at dp[maximumWeight]
    // But to be precise, we can find the maximum in the entire dp array
    return *std::max_element(dp.begin(), dp.end());
}

} // namespace knapsack

