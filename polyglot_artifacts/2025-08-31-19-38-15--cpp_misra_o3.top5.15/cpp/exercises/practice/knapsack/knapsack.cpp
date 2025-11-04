#include "knapsack.h"
#include <cstddef>
#include <vector>
#include <algorithm>

namespace knapsack
{

auto maximum_value(std::int32_t maximum_weight, const std::vector<Item> & items) noexcept -> std::int32_t
{
    if ((maximum_weight <= 0) || (items.empty()))
    {
        return 0;
    }

    /* Dynamic programming table: dp[w] holds the best value for exact weight w */
    std::vector<std::int32_t> dp(static_cast<std::size_t>(maximum_weight + 1), 0);

    for (auto const & itm : items)
    {
        for (std::int32_t w = maximum_weight; w >= itm.weight; --w)
        {
            auto const idx_current = static_cast<std::size_t>(w);
            auto const idx_prev = static_cast<std::size_t>(w - itm.weight);
            auto const potential_value = dp[idx_prev] + itm.value;

            if (potential_value > dp[idx_current])
            {
                dp[idx_current] = potential_value;
            }
        }
    }

    /* Return the best value achievable with weight not exceeding maximum_weight */
    return *std::max_element(dp.cbegin(), dp.cend());
}

} // namespace knapsack

