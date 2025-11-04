#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    // Handle case where maximumWeight is 0
    if (maximumWeight < 0)
    {
        return 0;
    }
    
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items)
    {
        // Handle items with weight 0 by always adding their value
        if (item.weight == 0)
        {
            // Since all values are strictly positive, we can always add them
            // But we need to add to every dp entry
            for (std::int32_t w = 0; w <= maximumWeight; w++)
            {
                dp[w] += item.value;
            }
        }
        else
        {
            // Process from the end to prevent reusing the same item
            for (std::int32_t w = maximumWeight; w >= item.weight; w--)
            {
                if (dp[w - item.weight] + item.value > dp[w])
                {
                    dp[w] = dp[w - item.weight] + item.value;
                }
            }
        }
    }
    
    // Find the maximum value in the dp array
    // If maximumWeight is 0, dp[0] will be the sum of all items with weight 0
    return *std::max_element(dp.begin(), dp.end());
}

} // namespace knapsack

