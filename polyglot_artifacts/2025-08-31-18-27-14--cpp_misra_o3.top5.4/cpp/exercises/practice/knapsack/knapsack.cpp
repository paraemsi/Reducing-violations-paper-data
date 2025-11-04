#include "knapsack.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace knapsack
{

auto maximum_value(std::uint32_t             capacity,
                   const std::vector<Item>& items) -> std::uint32_t
{
    /*  Space-optimised dynamic programming using a single row (1-D array).
     *  dp[w] – maximum value achievable without exceeding total weight w.
     *  Iterate capacities in descending order to guarantee each item is used
     *  at most once.
     */
    std::vector<std::uint32_t> dp(
        capacity + static_cast<std::uint32_t>(1U), 0U);

    for (const Item& current_item : items)
    {
        if (current_item.weight > capacity)
        {
            continue;
        }

        for (std::uint32_t w { capacity }; w >= current_item.weight; --w)
        {
            const std::uint32_t without_item { dp[w] };
            const std::uint32_t with_item {
                static_cast<std::uint32_t>(
                    dp[w - current_item.weight] + current_item.value) };

            dp[w] = std::max(without_item, with_item);

            /*  Prevent unsigned wrap-around when w == 0U                       */
            if (w == current_item.weight)
            {
                break;
            }
        }
    }

    return dp[capacity];
}

} // namespace knapsack

