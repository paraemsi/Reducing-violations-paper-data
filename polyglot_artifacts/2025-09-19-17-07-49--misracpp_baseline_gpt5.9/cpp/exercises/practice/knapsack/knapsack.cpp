#include "knapsack.h"

#include <algorithm>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items) noexcept
{
    if (capacity <= 0 || items.empty())
    {
        return 0;
    }

    const int W = capacity;
    std::vector<int> dp(W + 1, 0);

    for (const auto& item : items)
    {
        if (item.weight < 0)
        {
            // Skip items with negative weight (invalid input).
            continue;
        }

        if (item.weight > W)
        {
            // Cannot fit this item at any capacity up to W.
            continue;
        }

        // Iterate backwards to ensure each item is only used once (0/1 knapsack).
        for (int w = W; w >= item.weight; --w)
        {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }

    return dp[W];
}

} // namespace knapsack

