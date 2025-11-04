#include "knapsack.h"

#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(const std::vector<Item>& items, int capacity)
{
    int n = items.size();
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(capacity+1, 0));
    for (int i = 1; i <= n; ++i)
    {
        for (int w = 0; w <= capacity; ++w)
        {
            if (items[i-1].weight > w)
                dp[i][w] = dp[i-1][w];
            else
                dp[i][w] = std::max(dp[i-1][w], dp[i-1][w - items[i-1].weight] + items[i-1].value);
        }
    }
    return dp[n][capacity];
}

std::vector<int> optimal_item_indices(const std::vector<Item>& items, int capacity)
{
    int n = items.size();
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(capacity+1, 0));
    for (int i = 1; i <= n; ++i)
    {
        for (int w = 0; w <= capacity; ++w)
        {
            if (items[i-1].weight > w)
                dp[i][w] = dp[i-1][w];
            else
                dp[i][w] = std::max(dp[i-1][w], dp[i-1][w - items[i-1].weight] + items[i-1].value);
        }
    }
    // Backtrack to find which items were taken
    std::vector<int> indices;
    int w = capacity;
    for (int i = n; i >= 1; --i)
    {
        if (dp[i][w] != dp[i-1][w])
        {
            indices.push_back(i-1);
            w -= items[i-1].weight;
        }
    }
    std::reverse(indices.begin(), indices.end());
    return indices;
}

} // namespace knapsack

