#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int knapsackMaxValue(const std::vector<Item>& items, int maxWeight, std::vector<int>& taken)
{
    int n = static_cast<int>(items.size());
    // dp[i][w] = max value using first i items and weight limit w
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(maxWeight + 1, 0));

    // Build table
    for (int i = 1; i <= n; ++i) {
        int wt = items[i - 1].weight;
        int val = items[i - 1].value;
        for (int w = 0; w <= maxWeight; ++w) {
            if (wt > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - wt] + val);
            }
        }
    }

    // Backtrack to find which items were taken
    taken.clear();
    int w = maxWeight;
    for (int i = n; i > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            taken.push_back(i - 1); // item indices
            w -= items[i - 1].weight;
        }
    }
    // The taken vector is in reverse order, but order doesn't matter

    return dp[n][maxWeight];
}

int maximum_value(int maxWeight, const std::vector<Item>& items) {
    std::vector<int> dummy;
    return knapsack::knapsackMaxValue(items, maxWeight, dummy);
}

} // namespace knapsack

