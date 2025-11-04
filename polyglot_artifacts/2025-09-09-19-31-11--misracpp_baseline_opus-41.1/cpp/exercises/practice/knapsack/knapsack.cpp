#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int maximum_weight, const std::vector<Item>& items)
{
    if (maximum_weight <= 0 || items.empty())
    {
        return 0;
    }
    
    int n = items.size();
    
    // Create a 2D DP table
    // dp[i][w] represents the maximum value that can be obtained
    // with first i items and weight limit w
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(maximum_weight + 1, 0));
    
    // Build the DP table bottom-up
    for (int i = 1; i <= n; ++i)
    {
        for (int w = 0; w <= maximum_weight; ++w)
        {
            // Option 1: Don't take the current item
            dp[i][w] = dp[i - 1][w];
            
            // Option 2: Take the current item (if it fits)
            if (items[i - 1].weight <= w)
            {
                int value_with_item = dp[i - 1][w - items[i - 1].weight] + items[i - 1].value;
                dp[i][w] = std::max(dp[i][w], value_with_item);
            }
        }
    }
    
    return dp[n][maximum_weight];
}

} // namespace knapsack
