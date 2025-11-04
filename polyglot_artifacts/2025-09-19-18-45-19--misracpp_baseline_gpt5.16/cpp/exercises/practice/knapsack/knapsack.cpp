#include "knapsack.h"

#include <algorithm>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty())
    {
        return 0;
    }

    std::vector<int> dp(static_cast<std::size_t>(capacity) + 1, 0);

    for (const auto& it : items)
    {
        if (it.weight < 0 || it.value < 0)
        {
            // Ignore invalid entries (negative weight or value). Zero-weight items are allowed.
            continue;
        }

        for (int w = capacity; w >= it.weight; --w)
        {
            std::size_t ws = static_cast<std::size_t>(w);
            std::size_t w_prev = static_cast<std::size_t>(w - it.weight);
            dp[ws] = std::max(dp[ws], dp[w_prev] + it.value);
        }
    }

    return dp.back();
}

} // namespace knapsack

