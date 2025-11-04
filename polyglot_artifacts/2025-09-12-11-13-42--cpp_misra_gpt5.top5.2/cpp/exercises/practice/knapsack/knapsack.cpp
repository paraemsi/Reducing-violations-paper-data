#include "knapsack.h"
#include <cstddef>

namespace knapsack
{

std::uint32_t maximum_value(std::uint32_t maximum_weight, const std::vector<Item>& items) noexcept
{
    if ((maximum_weight == static_cast<std::uint32_t>(0U)) || (items.empty()))
    {
        return static_cast<std::uint32_t>(0U);
    }

    const std::size_t cap = static_cast<std::size_t>(maximum_weight);

    std::vector<std::uint32_t> dp;
    dp.assign((cap + static_cast<std::size_t>(1U)), static_cast<std::uint32_t>(0U));

    for (std::size_t i = static_cast<std::size_t>(0U); i < items.size(); ++i)
    {
        const std::uint32_t w = items[i].weight;
        const std::uint32_t v = items[i].value;

        if (w == static_cast<std::uint32_t>(0U))
        {
            for (std::size_t c2 = static_cast<std::size_t>(0U); c2 <= cap; ++c2)
            {
                dp[c2] = (dp[c2] + v);
            }
            continue;
        }

        std::size_t c = cap;
        while (c >= static_cast<std::size_t>(w))
        {
            const std::size_t idx = c;
            const std::size_t prev_idx = (c - static_cast<std::size_t>(w));

            const std::uint32_t candidate = (dp[prev_idx] + v);
            const std::uint32_t current = dp[idx];

            if (candidate > current)
            {
                dp[idx] = candidate;
            }

            c = (c - static_cast<std::size_t>(1U));
        }
    }

    return dp[cap];
}

} // namespace knapsack

