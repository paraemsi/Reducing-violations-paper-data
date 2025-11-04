#include "knapsack.h"
#include <algorithm>
#include <vector>

namespace knapsack
{

auto knapsack_max_value(const std::vector<Item>& items,
                        std::int32_t max_weight) -> std::int32_t
{
    const std::size_t capacity_sz =
        (static_cast<std::size_t>(max_weight) + static_cast<std::size_t>(1));

    std::vector<std::int32_t> dp(capacity_sz, static_cast<std::int32_t>(0));

    for (const Item& item : items)
    {
        for (std::int32_t w = max_weight; w >= item.weight; --w)
        {
            const std::size_t w_sz = static_cast<std::size_t>(w);
            const std::size_t w_minus_item_sz =
                static_cast<std::size_t>(w - item.weight);

            const std::int32_t candidate =
                (dp[w_minus_item_sz] + item.value);

            if (candidate > dp[w_sz])
            {
                dp[w_sz] = candidate;
            }
        }
    }

    /*  Return the maximum value that can be achieved without
     *  exceeding the supplied weight limit.  The best result may
     *  correspond to any weight ≤ max_weight, therefore take the
     *  maximum element stored in the DP array.
     */
    return *std::max_element(dp.cbegin(), dp.cend());
}

auto maximum_value(std::int32_t max_weight,
                   const std::vector<Item>& items) -> std::int32_t
{
    return knapsack_max_value(items, max_weight);
}

} // namespace knapsack

