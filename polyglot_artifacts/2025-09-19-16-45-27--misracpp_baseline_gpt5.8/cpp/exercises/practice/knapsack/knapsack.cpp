#include "knapsack.h"
#include <algorithm>
#include <cstddef>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty())
        return 0;

    std::vector<int> dp(static_cast<std::size_t>(capacity) + 1, 0);

    for (const auto& item : items)
    {
        if (item.value < 0 || item.weight < 0)
            continue;

        const int wt = item.weight;
        const int val = item.value;

        if (wt <= capacity)
        {
            for (int w = capacity; w >= wt; --w)
            {
                dp[static_cast<std::size_t>(w)] = std::max(
                    dp[static_cast<std::size_t>(w)],
                    dp[static_cast<std::size_t>(w - wt)] + val
                );
            }
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

