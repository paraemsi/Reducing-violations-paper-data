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

    std::vector<int> dp(static_cast<std::size_t>(capacity) + 1, 0);

    for (const auto& item : items)
    {
        const int w = item.weight;
        const int v = item.value;

        if (w <= 0)
        {
            // Zero or invalid (non-positive) weight: can be taken at most once.
            // It doesn't consume capacity, so it increases the value for all capacities.
            for (int cap = capacity; cap >= 0; --cap)
            {
                std::size_t cs = static_cast<std::size_t>(cap);
                dp[cs] = std::max(dp[cs], dp[cs] + v);
            }
        }
        else
        {
            // 0/1 knapsack transition using backward iteration to avoid reusing the same item.
            for (int cap = capacity; cap >= w; --cap)
            {
                std::size_t cs = static_cast<std::size_t>(cap);
                dp[cs] = std::max(dp[cs],
                                  dp[static_cast<std::size_t>(cap - w)] + v);
            }
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

