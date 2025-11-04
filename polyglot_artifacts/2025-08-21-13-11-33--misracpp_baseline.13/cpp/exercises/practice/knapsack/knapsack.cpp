#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstring>

namespace knapsack
{

// Returns the maximum value that can be put in a knapsack of capacity maxWeight.
// If 'taken' is not nullptr, it will be filled with a bool array of size itemCount
// indicating which items are taken (true) or not (false).
int knapsackMaxValue(const Item* items, int itemCount, int maxWeight, bool* taken)
{
    // DP table: dp[i][w] = max value using first i items and weight limit w
    std::vector<std::vector<int>> dp(itemCount + 1, std::vector<int>(maxWeight + 1, 0));

    for (int i = 1; i <= itemCount; ++i) {
        int wt = items[i-1].weight;
        int val = items[i-1].value;
        for (int w = 0; w <= maxWeight; ++w) {
            if (wt > w) {
                dp[i][w] = dp[i-1][w];
            } else {
                dp[i][w] = std::max(dp[i-1][w], dp[i-1][w-wt] + val);
            }
        }
    }

    if (taken) {
        // Backtrack to find which items are taken
        std::memset(taken, 0, sizeof(bool) * itemCount);
        int w = maxWeight;
        for (int i = itemCount; i > 0; --i) {
            if (dp[i][w] != dp[i-1][w]) {
                taken[i-1] = true;
                w -= items[i-1].weight;
            }
        }
    }

    return dp[itemCount][maxWeight];
}

// Implements the interface expected by the tests: maximum_value(int max_weight, const std::vector<Item>& items)
int maximum_value(int max_weight, const std::vector<Item>& items)
{
    int itemCount = static_cast<int>(items.size());
    // We don't need to track which items are taken for the test interface
    return knapsackMaxValue(items.data(), itemCount, max_weight, nullptr);
}

} // namespace knapsack

