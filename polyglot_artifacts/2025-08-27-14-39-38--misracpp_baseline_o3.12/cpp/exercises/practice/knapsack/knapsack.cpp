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

    std::vector<int> dp(static_cast<size_t>(capacity) + 1, 0);

    for (const auto& item : items)
    {
        if (item.weight > capacity)
        {
            continue; // Skip items that individually exceed capacity
        }

        for (int w = capacity; w >= item.weight; --w)
        {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }

    return dp[capacity];
}

} // namespace knapsack

