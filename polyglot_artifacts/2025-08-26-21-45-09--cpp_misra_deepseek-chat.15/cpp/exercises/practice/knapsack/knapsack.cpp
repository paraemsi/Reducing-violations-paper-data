#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    // Handle case when maximum weight is negative (though it should be non-negative per the problem)
    if (maximumWeight < 0)
    {
        return 0;
    }
    
    // Sum up values of items with weight 0
    std::int32_t zeroWeightValue = 0;
    std::vector<Item> remainingItems;
    for (const auto& item : items)
    {
        if (item.weight == 0)
        {
            if (item.value > 0)
            {
                zeroWeightValue += item.value;
            }
        }
        else
        {
            if (item.weight <= maximumWeight)
            {
                remainingItems.push_back(item);
            }
        }
    }
    
    // If maximumWeight is 0, we can only take items with weight 0
    if (maximumWeight == 0)
    {
        return zeroWeightValue;
    }
    
    // Initialize DP array
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : remainingItems)
    {
        for (std::int32_t w = maximumWeight; w >= item.weight; --w)
        {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }
    
    // Find maximum value in dp array and add zero weight items' value
    std::int32_t maxValue = 0;
    for (std::int32_t w = 0; w <= maximumWeight; ++w)
    {
        if (dp[w] > maxValue)
        {
            maxValue = dp[w];
        }
    }
    return maxValue + zeroWeightValue;
}

} // namespace knapsack

