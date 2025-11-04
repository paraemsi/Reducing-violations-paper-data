#include "knapsack.h"
#include <algorithm>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (items.empty())
    {
        return 0;
    }

    // Clamp capacity to non-negative for DP sizing.
    const int cap = std::max(0, capacity);

    // Sum values of zero-weight items (can always take each once).
    int zero_weight_value_sum = 0;

    std::vector<int> dp(cap + 1, 0);

    for (const auto& item : items)
    {
        const int w = item.weight;
        const int v = item.value;

        // Ignore invalid negative-weight items.
        if (w < 0)
        {
            continue;
        }

        if (w == 0)
        {
            zero_weight_value_sum += v;
            continue;
        }

        // 0/1 knapsack transition (iterate backwards to avoid reuse).
        for (int curr = cap; curr >= w; --curr)
        {
            dp[curr] = std::max(dp[curr], dp[curr - w] + v);
        }
    }

    return zero_weight_value_sum + dp[cap];
}

} // namespace knapsack

