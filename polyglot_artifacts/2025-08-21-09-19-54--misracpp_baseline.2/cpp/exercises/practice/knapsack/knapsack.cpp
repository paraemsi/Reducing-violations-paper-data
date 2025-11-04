#include "knapsack.h"

#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    int n = static_cast<int>(items.size());
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

std::vector<int> optimal_item_indices(int capacity, const std::vector<Item>& items)
{
    int n = static_cast<int>(items.size());
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    // Build DP table
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

    // Backtrack to find which items to take
    std::vector<int> indices;
    int w = capacity;
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

