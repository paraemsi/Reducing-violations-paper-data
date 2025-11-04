#include "knapsack.h"

#include <vector>

namespace knapsack
{

auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t
{
    std::vector<std::uint32_t> dp(capacity + 1U, 0U);

    for (const Item& it : items)
    {
        const std::uint32_t w = it.weight;
        const std::uint32_t v = it.value;

        /*  Guard against zero-weight items. A zero weight would cause the
            descending loop below to iterate indefinitely because the loop
            condition relies on             (j >= w)
            remaining false once j wraps around.                                */
        if (w == 0U)
        {
            continue;
        }

        for (std::uint32_t j = capacity; j >= w; --j)
        {
            const std::uint32_t candidate = dp[j - w] + v;
            if (candidate > dp[j])
            {
                dp[j] = candidate;
            }
        }
    }

    return dp[capacity];
}

} // namespace knapsack

