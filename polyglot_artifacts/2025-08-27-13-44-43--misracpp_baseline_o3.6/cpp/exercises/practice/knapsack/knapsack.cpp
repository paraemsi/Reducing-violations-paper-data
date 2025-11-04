#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int max_weight, const std::vector<Item>& items)
{
    if (max_weight <= 0 || items.empty())
    {
        return 0;
    }

    std::vector<int> dp(static_cast<std::size_t>(max_weight) + 1, 0);

    for (const auto &item : items)
    {
        if (item.weight > max_weight)
        {
            continue; // item can't fit, skip
        }

        for (int w = max_weight; w >= item.weight; --w)
        {
            dp[static_cast<std::size_t>(w)] =
                std::max(dp[static_cast<std::size_t>(w)],
                         dp[static_cast<std::size_t>(w - item.weight)] + item.value);
        }
    }

    return *std::max_element(dp.begin(), dp.end());
}

} // namespace knapsack

