#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty())
        return 0;

    std::vector<int> dp(capacity + 1, 0);

    for (const auto& item : items) {
        // iterate backwards so each item is considered only once
        for (int w = capacity; w >= item.weight; --w) {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }

    return dp[capacity];
}

} // namespace knapsack

