#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int max_weight, const std::vector<Item>& items)
{
    int n = items.size();
    std::vector<std::vector<int> > dp(n + 1, std::vector<int>(max_weight + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= n; ++i)
    {
        for (int w = 0; w <= max_weight; ++w)
        {
            if (items[i - 1].weight <= w)
            {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][max_weight];
}

} // namespace knapsack
