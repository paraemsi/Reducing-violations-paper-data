#include "knapsack.h"
#include <algorithm>
#include <cstddef>

namespace knapsack
{

int maximum_value(int maximum_weight, const std::vector<Item>& items)
{
    if (maximum_weight <= 0 || items.empty())
    {
        return 0;
    }

    // dp[w] = max value for capacity w
    std::vector<int> dp(static_cast<std::size_t>(maximum_weight) + 1, 0);

    for (const auto& item : items)
    {
        // Traverse weights in descending order to ensure 0/1 selection
        for (int w = maximum_weight; w >= item.weight; --w)
        {
            dp[static_cast<std::size_t>(w)] = std::max(
                dp[static_cast<std::size_t>(w)],
                dp[static_cast<std::size_t>(w - item.weight)] + item.value
            );
        }
    }

    return dp.back();
}

} // namespace knapsack

