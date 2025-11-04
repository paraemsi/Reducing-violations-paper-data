#include "knapsack.h"
#include <algorithm>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty())
    {
        return 0;
    }

    std::vector<int> dp(static_cast<size_t>(capacity) + 1, 0);

    for (const auto& it : items)
    {
        if (it.weight < 0 || it.value < 0)
        {
            // Ignore invalid negative entries defensively.
            continue;
        }
        // 0/1 knapsack: iterate weight descending to avoid reusing the same item
        for (int w = capacity; w >= it.weight; --w)
        {
            dp[static_cast<size_t>(w)] = std::max(
                dp[static_cast<size_t>(w)],
                dp[static_cast<size_t>(w - it.weight)] + it.value
            );
        }
    }

    return dp[static_cast<size_t>(capacity)];
}

} // namespace knapsack

