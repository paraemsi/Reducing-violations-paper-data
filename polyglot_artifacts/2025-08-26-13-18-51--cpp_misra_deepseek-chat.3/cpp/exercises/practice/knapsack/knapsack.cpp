#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    // Handle case where maximum weight is 0 or no items
    if (maximum_weight < 0)
    {
        return 0;
    }
    
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximum_weight) + 1, 0);
    
    for (const auto& item : items)
    {
        // Only process if the item's weight is non-negative
        // To ensure we don't use the same item multiple times, process from the end
        for (std::int32_t w = maximum_weight; w >= 0; --w)
        {
            // Check if we can include this item
            if (item.weight <= w)
            {
                std::int32_t remaining_weight = w - item.weight;
                std::int32_t new_value = dp[static_cast<std::size_t>(remaining_weight)] + item.value;
                if (new_value > dp[static_cast<std::size_t>(w)])
                {
                    dp[static_cast<std::size_t>(w)] = new_value;
                }
            }
        }
    }
    
    return dp[static_cast<std::size_t>(maximum_weight)];
}

} // namespace knapsack

