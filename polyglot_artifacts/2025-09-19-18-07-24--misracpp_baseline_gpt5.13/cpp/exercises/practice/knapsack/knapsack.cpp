#include "knapsack.h"
#include <algorithm>
#include <vector>

namespace knapsack
{

int maximum_value(int max_weight, const std::vector<Item>& items)
{
    if (max_weight <= 0) {
        int sum_zero = 0;
        for (const auto& it : items) {
            if (it.weight == 0 && it.value > 0) {
                sum_zero += it.value;
            }
        }
        return sum_zero;
    }

    const int W = max_weight;
    int sum_zero = 0;
    std::vector<int> dp(W + 1, 0);

    // Handle zero-weight items separately to avoid infinite gain in 1D DP.
    for (const auto& it : items) {
        if (it.weight == 0) {
            if (it.value > 0) {
                sum_zero += it.value;
            }
            continue;
        }
        if (it.weight < 0) {
            continue; // Ignore invalid negative-weight items
        }
        if (it.weight > W) {
            continue;
        }
        for (int w = W; w >= it.weight; --w) {
            dp[w] = std::max(dp[w], dp[w - it.weight] + it.value);
        }
    }

    return dp[W] + sum_zero;
}

} // namespace knapsack

