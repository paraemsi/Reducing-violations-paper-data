#include "knapsack.h"
#include <algorithm>
#include <cstddef>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty()) {
        return 0;
    }

    std::vector<int> dp(static_cast<std::size_t>(capacity + 1), 0);

    for (const auto& item : items)
    {
        // 0/1 knapsack: iterate capacity in descending order to avoid reusing the same item.
        for (int w = capacity; w >= item.weight; --w)
        {
            int with_item = dp[static_cast<std::size_t>(w - item.weight)] + item.value;
            dp[static_cast<std::size_t>(w)] = std::max(dp[static_cast<std::size_t>(w)], with_item);
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

