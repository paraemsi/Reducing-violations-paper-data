#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int knapsack_max_value(const std::vector<Item>& items, int capacity)
{
    int n = items.size();
    // dp[i][w] = max value using first i items and capacity w
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; ++i)
    {
        for (int w = 0; w <= capacity; ++w)
        {
            if (items[i - 1].weight > w)
            {
                dp[i][w] = dp[i - 1][w];
            }
            else
            {
                dp[i][w] = std::max(
                    dp[i - 1][w],
                    dp[i - 1][w - items[i - 1].weight] + items[i - 1].value
                );
            }
        }
    }
    return dp[n][capacity];
}

std::vector<int> knapsack_selected_items(const std::vector<Item>& items, int capacity)
{
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    // Fill dp table
    for (int i = 1; i <= n; ++i)
    {
        for (int w = 0; w <= capacity; ++w)
        {
            if (items[i - 1].weight > w)
            {
                dp[i][w] = dp[i - 1][w];
            }
            else
            {
                dp[i][w] = std::max(
                    dp[i - 1][w],
                    dp[i - 1][w - items[i - 1].weight] + items[i - 1].value
                );
            }
        }
    }
    // Backtrack to find selected items
    std::vector<int> selected;
    int w = capacity;
    for (int i = n; i >= 1; --i)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            selected.push_back(i - 1); // item i-1 is taken
            w -= items[i - 1].weight;
        }
    }
    std::reverse(selected.begin(), selected.end());
    return selected;
}

} // namespace knapsack

