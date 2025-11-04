#include "knapsack.h"

#include <vector>
#include <algorithm>

namespace knapsack
{

int knapsackMaxValue(const std::vector<Item>& items, int maxWeight, std::vector<int>* selected)
{
    int n = static_cast<int>(items.size());
    // dp[i][w] = max value using first i items and weight limit w
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(maxWeight + 1, 0));

    // Build table dp[][] in bottom up manner
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

    // If selected is requested, reconstruct the solution
    if (selected) {
        selected->clear();
        int w = maxWeight;
        for (int i = n; i >= 1; --i) {
            if (dp[i][w] != dp[i - 1][w]) {
                selected->push_back(i - 1); // item indices are 0-based
                w -= items[i - 1].weight;
            }
        }
        std::reverse(selected->begin(), selected->end());
    }

    return dp[n][maxWeight];
}

int maximum_value(int maxWeight, const std::vector<Item>& items)
{
    // Call the main implementation, ignore selected items
    return knapsackMaxValue(items, maxWeight, nullptr);
}

} // namespace knapsack

