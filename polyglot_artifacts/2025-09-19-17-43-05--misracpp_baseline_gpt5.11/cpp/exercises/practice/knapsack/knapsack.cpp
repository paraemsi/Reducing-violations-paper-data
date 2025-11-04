#include "knapsack.h"
#include <algorithm>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty())
        return 0;

    const int cap = capacity;
    std::vector<int> dp(static_cast<std::size_t>(cap + 1), 0);

    for (const auto& it : items)
    {
        if (it.weight < 0) {
            // Skip invalid negative-weight items
            continue;
        }

        const int w = it.weight;
        const int v = it.value;

        const int start = (w == 0) ? 0 : w;
        if (start > cap) {
            continue;
        }

        for (int c = cap; c >= start; --c)
        {
            dp[c] = std::max(dp[c], dp[c - w] + v);
        }
    }

    return dp[cap];
}

} // namespace knapsack

