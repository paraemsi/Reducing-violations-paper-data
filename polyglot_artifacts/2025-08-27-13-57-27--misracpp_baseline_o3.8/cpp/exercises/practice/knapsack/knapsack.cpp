#include "knapsack.h"

#include <algorithm>

namespace knapsack
{

int maximum_value(int max_weight, const std::vector<Item>& items)
{
    if (max_weight <= 0 || items.empty())
        return 0;

    // dp[w] holds the maximum value achievable with total weight w
    std::vector<int> dp(static_cast<std::size_t>(max_weight + 1), 0);

    for (const auto& item : items)
    {
        // iterate backwards to ensure each item is only used once (0/1 knapsack)
        for (int w = max_weight; w >= item.weight; --w)
        {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }

    return dp[max_weight];
}

} // namespace knapsack

