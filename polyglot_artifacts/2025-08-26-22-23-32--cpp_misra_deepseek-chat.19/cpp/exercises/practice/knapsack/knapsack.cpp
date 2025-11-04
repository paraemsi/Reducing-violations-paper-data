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
    
    // First, calculate the sum of values for items with weight 0
    std::int32_t zeroWeightValueSum = 0;
    for (const auto& item : items)
    {
        if (item.weight == 0)
        {
            zeroWeightValueSum += item.value;
        }
    }
    
    // Initialize DP array with the sum of zero weight items
    std::vector<std::int32_t> dp(maximumWeight + 1, zeroWeightValueSum);
    
    // Process items with weight > 0
    for (const auto& item : items)
    {
        if (item.weight > 0)
        {
            for (std::int32_t w = maximumWeight; w >= item.weight; --w)
            {
                if ((dp[w - item.weight] + item.value) > dp[w])
                {
                    dp[w] = dp[w - item.weight] + item.value;
                }
            }
        }
    }
    
    // Find the maximum value in the dp array
    // Since all values are non-negative, the maximum will be at the highest index
    // But to be safe, we can find the maximum element
    return *std::max_element(dp.begin(), dp.end());
}

} // namespace knapsack

