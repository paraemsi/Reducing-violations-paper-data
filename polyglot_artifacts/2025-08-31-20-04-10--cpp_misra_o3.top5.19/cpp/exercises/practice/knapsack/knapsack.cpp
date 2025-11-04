#include "knapsack.h"
#include <vector>
#include <cstddef>

namespace knapsack
{

auto maximum_value(std::uint32_t                 capacity,
                   const std::vector<Item>& items) -> std::uint32_t
{
    /* Dynamic programming approach: dp[w] stores the maximum value
     * achievable with weight limit w.
     */
    const std::size_t dpSize = (static_cast<std::size_t>(capacity) + 1U);
    std::vector<std::uint32_t> dp(dpSize, 0U);

    const std::size_t itemCount = items.size();

    for (std::size_t i = 0U; i < itemCount; ++i)
    {
        const std::uint32_t weight = items[i].weight;
        const std::uint32_t value  = items[i].value;

        /* Traverse weights in reverse order to ensure each item is counted once. */
        for (std::uint32_t w = capacity; w >= weight; --w)
        {
            const std::uint32_t candidate =
                (dp[(w - weight)] + value);

            if (candidate > dp[w])
            {
                dp[w] = candidate;
            }

            if (w == 0U)
            {
                break;
            }
        }
    }

    return dp[capacity];
}

} // namespace knapsack

