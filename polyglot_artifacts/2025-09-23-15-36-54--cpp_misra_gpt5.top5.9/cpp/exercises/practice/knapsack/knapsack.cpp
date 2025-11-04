#include "knapsack.h"
#include <cstddef>

namespace knapsack
{

std::uint32_t maximum_value(std::uint32_t max_weight, const std::vector<Item> &items)
{
    const std::size_t capN = static_cast<std::size_t>(max_weight);

    std::uint32_t sum_zero_values = static_cast<std::uint32_t>(0U);
    for (const Item &it : items)
    {
        if ((it.weight == 0) && (it.value > 0))
        {
            sum_zero_values = (sum_zero_values + static_cast<std::uint32_t>(it.value));
        }
    }

    const std::size_t dp_size = (capN + static_cast<std::size_t>(1U));
    std::vector<std::uint32_t> dp(dp_size, sum_zero_values);

    for (const Item &it : items)
    {
        if (it.weight <= 0)
        {
            continue;
        }

        const std::uint32_t weight_u = static_cast<std::uint32_t>(it.weight);
        const std::uint32_t value_u = static_cast<std::uint32_t>(it.value);
        const std::size_t wgt = static_cast<std::size_t>(weight_u);

        if (wgt > capN)
        {
            continue;
        }

        std::size_t w = capN;
        while (w >= wgt)
        {
            const std::uint32_t without_item = dp[w];
            const std::uint32_t with_item = (dp[(w - wgt)] + value_u);
            dp[w] = ((with_item > without_item) ? with_item : without_item);

            if (w == static_cast<std::size_t>(0U))
            {
                break;
            }

            --w;
        }
    }

    return dp[capN];
}

} // namespace knapsack

