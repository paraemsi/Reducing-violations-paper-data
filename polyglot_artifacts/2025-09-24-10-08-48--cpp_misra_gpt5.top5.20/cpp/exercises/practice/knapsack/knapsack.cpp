#include "knapsack.h"
#include <cstddef>
#include <vector>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    if ((maximum_weight <= static_cast<std::int32_t>(0)) || (items.empty()))
    {
        return static_cast<std::int32_t>(0);
    }

    std::int32_t cap = maximum_weight;
    if (cap < static_cast<std::int32_t>(0))
    {
        cap = static_cast<std::int32_t>(0);
    }

    const std::size_t W = static_cast<std::size_t>(cap);
    std::vector<std::int32_t> dp(W + static_cast<std::size_t>(1), static_cast<std::int32_t>(0));

    for (const Item& item : items)
    {
        const std::int32_t wt = static_cast<std::int32_t>(item.weight);
        const std::int32_t val = static_cast<std::int32_t>(item.value);

        if ((wt <= static_cast<std::int32_t>(0)) || (val <= static_cast<std::int32_t>(0)))
        {
            continue;
        }

        for (std::int32_t w = cap; w >= wt; --w)
        {
            const std::int32_t without = dp.at(static_cast<std::size_t>(w));
            const std::int32_t with = dp.at(static_cast<std::size_t>(w - wt)) + val;

            if (with > without)
            {
                dp.at(static_cast<std::size_t>(w)) = with;
            }
        }
    }

    return dp.at(W);
}

} // namespace knapsack

