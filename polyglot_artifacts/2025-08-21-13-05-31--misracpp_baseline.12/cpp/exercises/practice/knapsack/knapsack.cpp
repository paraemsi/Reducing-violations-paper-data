#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int knapsackMaxValue(const Item* items, int itemCount, int maxWeight)
{
    // Dynamic programming table: dp[w] = max value for weight w
    std::vector<int> dp(maxWeight + 1, 0);

    for (int i = 0; i < itemCount; ++i) {
        // Traverse backwards to ensure each item is only used once
        for (int w = maxWeight; w >= items[i].weight; --w) {
            dp[w] = std::max(dp[w], dp[w - items[i].weight] + items[i].value);
        }
    }
    return dp[maxWeight];
}

} // namespace knapsack

