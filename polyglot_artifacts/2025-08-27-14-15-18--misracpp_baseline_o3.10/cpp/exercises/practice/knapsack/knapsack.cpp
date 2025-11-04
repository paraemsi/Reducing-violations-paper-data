#include "knapsack.h"
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

    // dp[w] stores the best value achievable with weight exactly w (or <= w for current iteration)
    std::vector<int> dp(static_cast<std::size_t>(capacity) + 1, 0);

    for (const auto& item : items)
    {
        // Iterate backwards to ensure each item is considered only once (0/1 knapsack)
        for (int w = capacity; w >= item.weight; --w)
        {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }

    return dp[capacity];
}

} // namespace knapsack

