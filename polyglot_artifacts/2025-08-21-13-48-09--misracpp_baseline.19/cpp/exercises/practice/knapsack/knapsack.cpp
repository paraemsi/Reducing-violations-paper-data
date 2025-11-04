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

std::vector<int> knapsack_selected_items(const std::vector<Item>& items, int capacity)
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

    // Backtrack to find selected items
    std::vector<int> selected;
    int w = capacity;
    for (int i = n; i >= 1; --i)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            selected.push_back(i - 1);
            w -= items[i - 1].weight;
        }
    }
    std::reverse(selected.begin(), selected.end());
    return selected;
}

} // namespace knapsack

