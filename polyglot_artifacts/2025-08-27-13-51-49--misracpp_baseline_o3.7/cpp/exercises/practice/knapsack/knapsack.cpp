#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstddef>

namespace knapsack
{

[[nodiscard]] int maximum_value(int max_weight, const std::vector<Item>& items)
{
    if (max_weight <= 0 || items.empty())
    {
        return 0;
    }

    std::vector<int> dp(static_cast<std::size_t>(max_weight) + 1, 0);

    for (const auto &item : items)
    {
        // Skip items with non-positive attributes (should not occur per problem statement)
        if (item.weight <= 0 || item.value <= 0)
        {
            continue;
        }

        if (item.weight > max_weight)
        {
            // Too heavy, cannot fit even alone
            continue;
        }

        // Iterate backwards to ensure each item is only taken once
        for (int w = max_weight; w >= item.weight; --w)
        {
            // Convert indices to size_t to avoid signed/unsigned mismatch warnings
            const std::size_t ws   = static_cast<std::size_t>(w);
            const std::size_t prev = static_cast<std::size_t>(w - item.weight);

            dp[ws] = std::max(dp[ws], dp[prev] + item.value);
        }
    }

    return dp[max_weight];
}

} // namespace knapsack

