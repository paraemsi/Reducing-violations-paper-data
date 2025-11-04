#include "knapsack.h"
#include <vector>
#include <cstddef>

namespace knapsack
{

int maximum_value(int capacity, const Items& items)
{
    if (capacity <= 0 || items.empty())
    {
        return 0;
    }

    std::vector<int> dp(static_cast<std::size_t>(capacity + 1), 0);

    for (const auto& item : items)
    {
        int w = item.weight;
        int v = item.value;
        if (w > capacity)
        {
            // Item too heavy for the knapsack; skip.
            continue;
        }
        // Iterate capacities in descending order to ensure 0/1 item usage.
        for (int c = capacity; c >= w; --c)
        {
            int candidate = dp[static_cast<std::size_t>(c - w)] + v;
            if (candidate > dp[static_cast<std::size_t>(c)])
            {
                dp[static_cast<std::size_t>(c)] = candidate;
            }
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

