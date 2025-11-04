#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty()) {
        return 0;
    }

    // dp[w] will hold the maximum value achievable with total weight exactly `w`
    std::vector<int> dp(static_cast<std::size_t>(capacity + 1), 0);

    for (const auto &item : items)
    {
        // Traverse weights in descending order to ensure each item is used at most once
        for (int w = capacity; w >= item.weight; --w)
        {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }

    // The optimal value is the maximum of all achievable values for
    // weights up to the capacity (the knapsack doesn’t have to be filled
    // exactly).
    return *std::max_element(dp.begin(), dp.end());
}

} // namespace knapsack

