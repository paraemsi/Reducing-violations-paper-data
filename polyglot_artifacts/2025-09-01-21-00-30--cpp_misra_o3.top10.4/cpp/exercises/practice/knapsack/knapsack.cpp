#include "knapsack.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace knapsack
{

[[nodiscard]] auto maximum_value(std::uint32_t capacity,
                                 const std::vector<Item>& items) -> std::uint32_t
{
    /* Dynamic-programming table: dp[w] holds the best value achievable
     * with total weight exactly w. The table is built iteratively.
     */
    std::vector<std::uint32_t> dp(
        static_cast<std::size_t>(capacity) + 1U, 0U);

    for (const Item& item : items)
    {
        /* Iterate weights in reverse to avoid re-using the same item
         * multiple times.
         */
        for (std::uint32_t w = capacity; w >= item.weight; --w)
        {
            const std::size_t w_idx      = static_cast<std::size_t>(w);
            const std::size_t prev_idx   =
                static_cast<std::size_t>(w - item.weight);

            const std::uint32_t candidate =
                dp[prev_idx] + item.value;

            if ((candidate > dp[w_idx]))
            {
                dp[w_idx] = candidate;
            }

            /* Prevent unsigned wrap-around when w reaches item.weight */
            if (w == item.weight)
            {
                break;
            }
        }
    }

    /* The optimal solution might use less than the full capacity.
     * Retrieve the maximum value achievable for any permissible weight.
     */
    const auto best_it =
        std::max_element(dp.cbegin(), dp.cend());

    return (best_it != dp.cend()) ? *best_it : 0U;
}

} // namespace knapsack

