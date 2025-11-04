#include "knapsack.h"
#include <algorithm>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item> &items)
{
    if (capacity <= 0 || items.empty())
    {
        return 0;
    }

    // dp[w] stores the maximum value achievable with total weight exactly w
    std::vector<int> dp(static_cast<std::size_t>(capacity) + 1, 0);

    for (const auto &item : items)
    {
        // Skip items with non-positive weight or value, they cannot improve the solution
        if (item.weight <= 0 || item.value <= 0)
        {
            continue;
        }

        // Traverse weights backwards so each item is considered only once
        for (int w = capacity; w >= item.weight; --w)
        {
            dp[static_cast<std::size_t>(w)] = std::max(
                dp[static_cast<std::size_t>(w)],
                dp[static_cast<std::size_t>(w - item.weight)] + item.value);
        }
    }

    // The best value might be achieved with a total weight **less than**
    // the full capacity, so return the maximum across all attainable weights.
    return *std::max_element(dp.begin(), dp.end());
}


} // namespace knapsack

