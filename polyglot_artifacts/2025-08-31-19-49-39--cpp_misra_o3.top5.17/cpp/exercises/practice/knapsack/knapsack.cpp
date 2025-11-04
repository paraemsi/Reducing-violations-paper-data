#include "knapsack.h"

#include <algorithm>   // for std::max, std::max_element
#include <vector>      // for std::vector
#include <cstddef>     // for std::size_t

namespace knapsack
{

static auto max_value(const std::vector<Item>& items, std::uint32_t capacity) -> std::uint32_t
{
    /* Dynamic programming table: dp[w] stores best value for weight w. */
    std::vector<std::uint32_t> dp(static_cast<std::size_t>(capacity) + 1U, 0U);

    for (const Item& item : items)
    {
        const std::uint32_t wt { item.weight };
        const std::uint32_t val { item.value };

        /* Iterate weights in reverse so each item is considered only once. */
        for (std::uint32_t w = capacity; (w >= wt) && (w <= capacity); --w)
        {
            const std::size_t idx { static_cast<std::size_t>(w) };
            const std::size_t idx_prev { static_cast<std::size_t>(w - wt) };

            const std::uint32_t candidate { val + dp[idx_prev] };
            dp[idx] = std::max(dp[idx], candidate);

            if (w == 0U)
            {
                break; /* Prevent unsigned wrap-around on next --w */
            }
        }
    }

    return *std::max_element(dp.cbegin(), dp.cend());
}

auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t
{
    return max_value(items, capacity);
}

} // namespace knapsack

