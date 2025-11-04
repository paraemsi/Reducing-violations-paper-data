#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    if ((items.empty()) || (maximumWeight == 0))
    {
        return 0;
    }
    
    // Create a DP array where dp[w] stores maximum value for weight w
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximumWeight) + 1, 0);
    
    for (const auto& item : items)
    {
        // To avoid reusing the same item, process from the end
        for (std::int32_t w = maximumWeight; w >= item.weight; --w)
        {
            if (dp[static_cast<std::size_t>(w)] < (dp[static_cast<std::size_t>(w - item.weight)] + item.value))
            {
                dp[static_cast<std::size_t>(w)] = dp[static_cast<std::size_t>(w - item.weight)] + item.value;
            }
        }
    }
    
    // Find the maximum value in the dp array
    return *std::max_element(dp.begin(), dp.end());
}

} // namespace knapsack

