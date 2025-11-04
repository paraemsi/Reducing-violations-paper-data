#include "knapsack.h"
#include <algorithm>
#include <vector>

namespace knapsack
{

int maximum_value(int maximum_weight, const std::vector<Item>& items)
{
    if (maximum_weight <= 0 || items.empty())
        return 0;

    std::vector<int> dp(static_cast<std::size_t>(maximum_weight + 1), 0);

    for (const auto& it : items)
    {
        // Skip invalid items (non-positive weight or value)
        if (it.weight <= 0 || it.value <= 0)
            continue;

        for (int w = maximum_weight; w >= it.weight; --w)
        {
            dp[static_cast<std::size_t>(w)] = std::max(
                dp[static_cast<std::size_t>(w)],
                dp[static_cast<std::size_t>(w - it.weight)] + it.value
            );
        }
    }

    return dp[static_cast<std::size_t>(maximum_weight)];
}

} // namespace knapsack

