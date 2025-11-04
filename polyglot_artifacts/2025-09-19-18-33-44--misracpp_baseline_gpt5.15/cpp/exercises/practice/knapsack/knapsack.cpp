#include "knapsack.h"
#include <algorithm>
#include <cstddef>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity < 0 || items.empty())
    {
        return 0;
    }

    // dp[w] will hold the maximum value achievable with capacity w
    std::vector<int> dp(static_cast<std::size_t>(capacity) + 1, 0);

    for (const auto& item : items)
    {
        // Skip items with negative weight to avoid invalid states.
        // Zero-weight items are allowed and can be taken at most once.
        if (item.weight < 0)
        {
            continue;
        }

        // Iterate backwards to ensure each item is used at most once (0/1 knapsack)
        for (int w = capacity; w >= item.weight; --w)
        {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }

    return dp[capacity];
}

} // namespace knapsack

