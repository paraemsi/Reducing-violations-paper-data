#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    if ((maximum_weight == 0) || (items.empty()))
    {
        return 0;
    }
    
    std::vector<std::int32_t> dp(maximum_weight + 1, 0);
    
    for (const auto& item : items)
    {
        for (std::int32_t w = maximum_weight; w >= item.weight; --w)
        {
            if (dp[w] < (dp[w - item.weight] + item.value))
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    return dp[maximum_weight];
}

} // namespace knapsack

