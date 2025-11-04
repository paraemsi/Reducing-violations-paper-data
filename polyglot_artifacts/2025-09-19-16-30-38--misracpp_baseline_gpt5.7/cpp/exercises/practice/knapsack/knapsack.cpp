#include "knapsack.h"
#include <cstddef>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
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

        if (v <= 0 || w < 0)
        {
            // Skip invalid items; weights should be non-negative and values positive.
            continue;
        }

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

