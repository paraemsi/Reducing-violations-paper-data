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
    
    // Use size_t for indices to match vector sizes
    const std::size_t numItems = items.size();
    
    // DP array to store maximum value for each weight
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximumWeight) + 1, 0);
    
    // Fill the DP array
    for (std::size_t i = 0; i < numItems; i++)
    {
        const Item& currentItem = items[i];
        // Process weights in reverse to avoid reusing the same item
        for (std::int32_t w = maximumWeight; w >= 0; w--)
        {
            if (currentItem.weight <= w)
            {
                const std::int32_t remainingWeight = (w - currentItem.weight);
                dp[static_cast<std::size_t>(w)] = std::max(
                    dp[static_cast<std::size_t>(w)], 
                    (dp[static_cast<std::size_t>(remainingWeight)] + currentItem.value)
                );
            }
        }
    }
    
    return dp[static_cast<std::size_t>(maximumWeight)];
}

} // namespace knapsack

