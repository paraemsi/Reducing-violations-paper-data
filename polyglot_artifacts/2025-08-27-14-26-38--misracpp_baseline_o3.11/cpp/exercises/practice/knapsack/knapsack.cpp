#include "knapsack.h"
#include <algorithm>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity == 0 || items.empty())
    {
        return 0;
    }

    // One-dimensional DP array where dp[w] holds the best value for weight w.
    std::vector<int> dp(static_cast<std::size_t>(capacity) + 1, 0);

    for (const auto& item : items)
    {
        // Traverse backwards to ensure each item is considered at most once.
        for (int w = capacity; w >= item.weight; --w)
        {
            dp[static_cast<std::size_t>(w)] =
                std::max(dp[static_cast<std::size_t>(w)],
                         dp[static_cast<std::size_t>(w - item.weight)] + item.value);
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

