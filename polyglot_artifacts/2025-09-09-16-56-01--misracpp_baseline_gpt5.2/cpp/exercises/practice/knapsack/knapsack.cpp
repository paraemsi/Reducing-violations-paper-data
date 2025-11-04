#include "knapsack.h"
#include <algorithm>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items) noexcept
{
    if (capacity <= 0 || items.empty())
        return 0;

    // Use 1D dynamic programming for 0/1 knapsack: O(n * capacity) time, O(capacity) space.
    std::vector<int> dp(static_cast<std::size_t>(capacity + 1), 0);
    int zero_weight_bonus = 0;

    for (const auto& it : items)
    {
        // Skip non-positive value items; they never help.
        if (it.value <= 0)
            continue;

        // Handle zero or negative weight items: include at most once as a free bonus.
        if (it.weight <= 0) {
            zero_weight_bonus += it.value;
            continue;
        }

        // Traverse weights descending to avoid reusing the same item multiple times.
        for (int w = capacity; w >= it.weight; --w)
        {
            dp[static_cast<std::size_t>(w)] =
                std::max(dp[static_cast<std::size_t>(w)],
                         dp[static_cast<std::size_t>(w - it.weight)] + it.value);
        }
    }

    return dp[static_cast<std::size_t>(capacity)] + zero_weight_bonus;
}

} // namespace knapsack

