#include "knapsack.h"
#include <cstddef>
#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty())
        return 0;

    std::vector<int> dp(static_cast<std::size_t>(capacity) + 1, 0);

    for (const auto& item : items)
    {
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

