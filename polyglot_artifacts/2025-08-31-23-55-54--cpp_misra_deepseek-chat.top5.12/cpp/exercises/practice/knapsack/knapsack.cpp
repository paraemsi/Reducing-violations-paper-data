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
    
    // To save space, we can use a 1D array
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items) 
    {
        // We need to iterate backwards to prevent reusing the same item
        for (std::int32_t w = maximumWeight; w >= item.weight; w--) 
        {
            if ((dp[w - item.weight] + item.value) > dp[w]) 
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    return dp[maximumWeight];
}

} // namespace knapsack

