#include "knapsack.h"
#include <cstddef>   // for std::size_t
#include <vector>
#include <algorithm>

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
        if (item.weight <= 0 || item.value <= 0)
        {
            // Skip invalid items; constraints say values are positive.
            continue;
        }

        for (int w = capacity; w >= item.weight; --w)
        {
            std::size_t ws = static_cast<std::size_t>(w);
            dp[ws] = std::max(dp[ws],
                              dp[ws - static_cast<std::size_t>(item.weight)] + item.value);
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

