#include "knapsack.h"

#include <cstddef>
#include <vector>

namespace knapsack
{

value_type maximum_value(weight_type maximum_weight, const std::vector<Item>& items)
{
    value_type base_zero_value = static_cast<value_type>(0U);

    const std::size_t max_w = static_cast<std::size_t>(maximum_weight);
    std::vector<value_type> dp((max_w + static_cast<std::size_t>(1U)), static_cast<value_type>(0U));

    for (const Item& it : items)
    {
        const weight_type w = it.weight;
        const value_type v = it.value;

        if (w == static_cast<weight_type>(0U))
        {
            base_zero_value = static_cast<value_type>(base_zero_value + v);
            continue;
        }

        const std::size_t w_s = static_cast<std::size_t>(w);

        for (std::size_t cap = (max_w + static_cast<std::size_t>(1U)); (cap-- > w_s); )
        {
            const value_type candidate = static_cast<value_type>(dp[(cap - w_s)] + v);
            dp[cap] = ((dp[cap] < candidate) ? candidate : dp[cap]);
        }
    }

    const value_type result = static_cast<value_type>(dp[max_w] + base_zero_value);
    return result;
}

} // namespace knapsack

