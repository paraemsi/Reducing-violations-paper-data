#include "knapsack.h"

#include <vector>
#include <algorithm>

namespace knapsack
{

int knapsackMaxValue(const std::vector<Item>& items, int maxWeight)
{
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(maxWeight + 1, 0));

    for (int i = 1; i <= n; ++i)
    {
        for (int w = 0; w <= maxWeight; ++w)
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
    return dp[n][maxWeight];
}

std::vector<std::size_t> knapsackSelectedItems(const std::vector<Item>& items, int maxWeight)
{
    int n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(maxWeight + 1, 0));

    // Fill DP table
    for (int i = 1; i <= n; ++i)
    {
        for (int w = 0; w <= maxWeight; ++w)
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
    std::vector<std::size_t> selected;
    int w = maxWeight;
    for (int i = n; i >= 1; --i)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            selected.push_back(static_cast<std::size_t>(i - 1));
            w -= items[i - 1].weight;
        }
    }
    std::reverse(selected.begin(), selected.end());
    return selected;
}

int maximum_value(int max_weight, const std::vector<Item>& items)
{
    // The test expects (max_weight, items), but our main function is (items, maxWeight)
    return knapsackMaxValue(items, max_weight);
}

} // namespace knapsack

