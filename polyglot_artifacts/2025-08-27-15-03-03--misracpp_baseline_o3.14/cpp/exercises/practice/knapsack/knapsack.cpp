#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstddef>   // for std::size_t

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty())
    {
        return 0;
    }

    // dp[w] holds the best value attainable with total weight w
    std::vector<int> dp(static_cast<std::size_t>(capacity) + 1, 0);

    for (const auto &item : items)
    {
        // iterate weights backwards to ensure each item is used at most once
        for (int w = capacity; w >= item.weight; --w)
        {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }

    return dp[capacity];
}

} // namespace knapsack

