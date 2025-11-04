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
    // Handle case where maximum weight is 0
    if (maximumWeight == 0)
    {
        // We can only take items with weight 0, which would contribute to the value
        // But according to the problem, all values are strictly positive, so if weight is 0, value is positive
        // However, the weight limit is 0, so we can't take any items with weight > 0
        // So find items with weight == 0 and sum their values
        std::int32_t total = 0;
        for (const auto& item : items)
        {
            if (item.weight == 0)
            {
                total += item.value;
            }
        }
        return total;
    }
    if (items.empty())
    {
        return 0;
    }
    
    // Create a DP array where dp[w] = maximum value with weight exactly w
    // But to find maximum up to maximumWeight, we can track the maximum at each step
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items)
    {
        // Only process if the item's weight is not greater than maximumWeight
        // To avoid reusing the same item, we process from the end
        for (std::int32_t w = maximumWeight; w >= item.weight; --w)
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
    
    // Find the maximum value in the dp array up to maximumWeight
    // Since values are non-negative, dp is non-decreasing, so the maximum is at the end
    // But to be safe, we find the maximum
    return *std::max_element(dp.begin(), dp.end());
}

} // namespace knapsack

