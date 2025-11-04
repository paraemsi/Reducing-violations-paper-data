#include "knapsack.h"
#include <algorithm>
#include <vector>
#include <cstddef>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty())
    {
        return 0;
    }

    // 1D DP: dp[w] = maximum value achievable with capacity w
    std::vector<int> dp(static_cast<std::size_t>(capacity + 1), 0);

    for (const auto& it : items)
    {
        // Ignore non-positive weights to avoid undefined behavior
        if (it.weight <= 0)
        {
            continue;
        }

        // Traverse backwards to ensure each item is used at most once (0/1 knapsack)
        for (int w = capacity; w >= it.weight; --w)
        {
            dp[static_cast<std::size_t>(w)] = std::max(
                dp[static_cast<std::size_t>(w)],
                dp[static_cast<std::size_t>(w - it.weight)] + it.value
            );
        }
    }

    return dp.back();
}

} // namespace knapsack

