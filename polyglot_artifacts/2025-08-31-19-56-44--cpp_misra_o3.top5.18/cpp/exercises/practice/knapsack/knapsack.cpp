#include "knapsack.h"

#include <cstdint>
#include <vector>

namespace knapsack
{

auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t
{
    /* Dynamic-programming table: dp[w] == best value achievable with total weight w */
    std::vector<std::uint32_t> dp(capacity + static_cast<std::uint32_t>(1U),
                                  static_cast<std::uint32_t>(0U));

    for (const Item& it : items)
    {
        /* Traverse weights in descending order to ensure each item is considered once */
        for (std::int32_t w = static_cast<std::int32_t>(capacity);
             w >= static_cast<std::int32_t>(it.weight);
             --w)
        {
            const std::uint32_t wu        = static_cast<std::uint32_t>(w);
            const std::uint32_t candidate =
                (dp[(wu - it.weight)] + it.value); /* value if item is taken */

            if (candidate > dp[wu])
            {
                dp[wu] = candidate;
            }
        }
    }

    return dp[capacity];
}

} // namespace knapsack

