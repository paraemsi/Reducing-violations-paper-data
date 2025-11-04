#include "knapsack.h"
#include <vector>
#include <cstddef> // for std::size_t
#include <algorithm> // for std::max

namespace knapsack
{

value_type maximum_value(weight_type max_weight, const std::vector<Item>& items)
{
    // Defensive: treat negative max_weight as zero
    if (max_weight <= static_cast<weight_type>(0))
    {
        return static_cast<value_type>(0);
    }

    const std::size_t n = items.size();
    std::vector<std::vector<value_type>> dp(
        (n + static_cast<std::size_t>(1)),
        std::vector<value_type>(static_cast<std::size_t>(max_weight) + static_cast<std::size_t>(1), static_cast<value_type>(0))
    );

    for (std::size_t i = static_cast<std::size_t>(1); i <= n; ++i)
    {
        for (weight_type w = static_cast<weight_type>(0); w <= max_weight; ++w)
        {
            if (w >= items[i - static_cast<std::size_t>(1)].weight)
            {
                value_type include = dp[i - static_cast<std::size_t>(1)][w - items[i - static_cast<std::size_t>(1)].weight] + items[i - static_cast<std::size_t>(1)].value;
                value_type exclude = dp[i - static_cast<std::size_t>(1)][w];
                dp[i][w] = (std::max)(include, exclude);
            }
            else
            {
                dp[i][w] = dp[i - static_cast<std::size_t>(1)][w];
            }
        }
    }
    return dp[n][max_weight];
}

} // namespace knapsack

