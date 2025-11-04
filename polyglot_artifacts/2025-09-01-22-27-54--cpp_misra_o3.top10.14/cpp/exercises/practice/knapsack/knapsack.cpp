#include "knapsack.h"
#include <cstddef>

namespace knapsack
{

std::uint32_t maximum_value(std::uint32_t capacity, const std::vector<Item>& items)
{
    /* Dynamic programming table where dp[w] holds the maximum value for
       weight limit w. */
    std::vector<std::uint32_t> dp(
        static_cast<std::size_t>(capacity + 1U), 0U);

    for (std::size_t i = 0U; i < items.size(); ++i)
    {
        const std::uint32_t weight = items[i].weight;
        const std::uint32_t value  = items[i].value;

        if (weight > capacity)
        {
            continue;
        }

        /* Handle zero-weight items separately to avoid unsigned wrap-around */
        if (weight == 0U)
        {
            for (std::uint32_t c = 0U; c <= capacity; ++c)
            {
                const std::uint32_t candidate = (dp[c] + value);
                if ((candidate > dp[c]))
                {
                    dp[c] = candidate;
                }
            }
            continue;
        }

        for (std::uint32_t c = capacity; c >= weight; --c)
        {
            const std::uint32_t candidate =
                (dp[static_cast<std::size_t>(c - weight)] + value);
            if ((candidate > dp[c]))
            {
                dp[c] = candidate;
            }
        }
    }

    return dp[capacity];
}

} // namespace knapsack

