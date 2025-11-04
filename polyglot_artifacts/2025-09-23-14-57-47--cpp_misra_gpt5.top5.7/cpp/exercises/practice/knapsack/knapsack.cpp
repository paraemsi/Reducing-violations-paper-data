#include "knapsack.h"
#include <cstddef>
#include <vector>

namespace knapsack
{

value_t maximum_value(weight_t max_weight, const std::vector<Item>& items)
{
    const weight_t cap = (max_weight > static_cast<weight_t>(0)) ? max_weight : static_cast<weight_t>(0);
    const std::size_t cap_z = static_cast<std::size_t>(cap);

    std::vector<value_t> dp(cap_z + static_cast<std::size_t>(1U), static_cast<value_t>(0));

    for (const Item& it : items)
    {
        const weight_t item_weight = static_cast<weight_t>(it.weight);
        const value_t item_value = static_cast<value_t>(it.value);

        if ((item_weight <= cap) && (item_weight > static_cast<weight_t>(0)))
        {
            for (weight_t w = cap; (w >= item_weight); --w)
            {
                const std::size_t w_idx = static_cast<std::size_t>(w);
                const std::size_t prev_idx = static_cast<std::size_t>(w - item_weight);
                const value_t candidate = static_cast<value_t>(dp[prev_idx] + item_value);

                if ((candidate > dp[w_idx]))
                {
                    dp[w_idx] = candidate;
                }
                else
                {
                    // no update
                }
            }
        }
        else
        {
            // skip items that are heavier than the capacity or non-positive weight
        }
    }

    return dp[cap_z];
}

} // namespace knapsack

