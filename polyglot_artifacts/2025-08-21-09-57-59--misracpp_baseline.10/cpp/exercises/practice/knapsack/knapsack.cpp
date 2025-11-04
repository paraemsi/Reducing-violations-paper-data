#include "knapsack.h"

#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(const std::vector<Item>& items, int capacity)
{
    int n = static_cast<int>(items.size());
    // dp[i][w]: max value using first i items with capacity w
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        int wt = items[i - 1].weight;
        int val = items[i - 1].value;
        for (int w = 0; w <= capacity; ++w)
        {
            if (wt > w)
                dp[i][w] = dp[i - 1][w];
            else
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - wt] + val);
        }
    }
    return dp[n][capacity];
}

} // namespace knapsack

