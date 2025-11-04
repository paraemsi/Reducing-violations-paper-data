#include "knapsack.h"
#include <vector>
#include <cstddef> // for std::size_t
#include <algorithm> // for std::max

namespace knapsack
{

value_type maximum_value(weight_type capacity, const std::vector<Item>& items)
{
    if (capacity <= static_cast<weight_type>(0))
    {
        return static_cast<value_type>(0);
    }

    const std::size_t n = items.size();
    std::vector<std::vector<value_type>> dp(
        (n + static_cast<std::size_t>(1)),
        std::vector<value_type>(static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1), static_cast<value_type>(0))
    );

    for (std::size_t i = static_cast<std::size_t>(1); i <= n; ++i)
    {
        const weight_type item_weight = items[i - static_cast<std::size_t>(1)].weight;
        const value_type item_value = items[i - static_cast<std::size_t>(1)].value;
        for (weight_type w = static_cast<weight_type>(0); w <= capacity; ++w)
        {
            if (w >= item_weight)
            {
                dp[i][static_cast<std::size_t>(w)] = std::max(
                    dp[i - static_cast<std::size_t>(1)][static_cast<std::size_t>(w)],
                    (dp[i - static_cast<std::size_t>(1)][static_cast<std::size_t>(w - item_weight)] + item_value)
                );
            }
            else
            {
                dp[i][static_cast<std::size_t>(w)] = dp[i - static_cast<std::size_t>(1)][static_cast<std::size_t>(w)];
            }
        }
    }
    return dp[n][static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

