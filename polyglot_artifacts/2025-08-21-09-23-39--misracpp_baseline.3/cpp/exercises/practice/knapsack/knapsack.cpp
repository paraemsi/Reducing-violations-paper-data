#include "knapsack.h"

#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int max_weight, const std::vector<Item>& items)
{
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(max_weight + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        int wt = items[i - 1].weight;
        int val = items[i - 1].value;
        for (int w = 0; w <= max_weight; ++w)
        {
            if (wt > w)
                dp[i][w] = dp[i - 1][w];
            else
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - wt] + val);
        }
    }
    return dp[n][max_weight];
}

std::vector<int> optimal_item_indices(int max_weight, const std::vector<Item>& items)
{
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(max_weight + 1, 0));

    // Fill DP table
    for (int i = 1; i <= n; ++i)
    {
        int wt = items[i - 1].weight;
        int val = items[i - 1].value;
        for (int w = 0; w <= max_weight; ++w)
        {
            if (wt > w)
                dp[i][w] = dp[i - 1][w];
            else
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - wt] + val);
        }
    }

    // Backtrack to find which items were taken
    std::vector<int> indices;
    int w = max_weight;
    for (int i = n; i >= 1; --i)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            indices.push_back(i - 1);
            w -= items[i - 1].weight;
        }
    }
    std::reverse(indices.begin(), indices.end());
    return indices;
}

} // namespace knapsack

