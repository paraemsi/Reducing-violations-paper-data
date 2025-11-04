#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int maximum_weight, const std::vector<Item>& items)
{
    if (items.empty()) return 0;
    
    // DP array where dp[w] = maximum value for weight w
    std::vector<int> dp(maximum_weight + 1, 0);
    
    for (const auto& item : items)
    {
        // Process from the end to prevent reusing the same item
        for (int w = maximum_weight; w >= item.weight; --w)
        {
            if (dp[w - item.weight] + item.value > dp[w])
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // The maximum value will be at dp[maximum_weight]
    return dp[maximum_weight];
}

} // namespace knapsack

