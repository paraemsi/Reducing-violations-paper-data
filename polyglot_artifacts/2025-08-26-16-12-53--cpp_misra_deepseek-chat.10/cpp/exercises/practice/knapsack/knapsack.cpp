#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    if ((items.empty()) || (maximum_weight == 0))
    {
        return 0;
    }
    
    // Create a DP array where dp[i] is the maximum value with weight i
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximum_weight) + 1, 0);
    
    for (const auto& item : items)
    {
        // To avoid reusing the same item, process from the end
        for (std::int32_t w = maximum_weight; w >= item.weight; --w)
        {
            std::int32_t const new_value = dp[static_cast<std::size_t>(w) - static_cast<std::size_t>(item.weight)] + item.value;
            if (dp[static_cast<std::size_t>(w)] < new_value)
            {
                dp[static_cast<std::size_t>(w)] = new_value;
            }
        }
    }
    
    // Find the maximum value in the dp array
    std::int32_t max_value = 0;
    for (std::int32_t w = 0; w <= maximum_weight; ++w)
    {
        if (dp[static_cast<std::size_t>(w)] > max_value)
        {
            max_value = dp[static_cast<std::size_t>(w)];
        }
    }
    
    return max_value;
}

} // namespace knapsack

