#include "knapsack.h"

#include <cstdint>
#include <vector>

namespace
{
    std::uint32_t compute_maximum_value_impl(std::uint32_t capacity, const std::vector<knapsack::Item>& items)
    {
        if (capacity == static_cast<std::uint32_t>(0U))
        {
            return static_cast<std::uint32_t>(0U);
        }

        std::vector<std::uint32_t> dp(static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1U), static_cast<std::uint32_t>(0U));

        for (const knapsack::Item& it : items)
        {
            // Skip any non-positive weights or values to avoid undefined/undesired behavior.
            if ((it.weight == static_cast<std::uint32_t>(0U)) || (it.value == static_cast<std::uint32_t>(0U)))
            {
                continue;
            }

            // Convert to fixed-width unsigned types after validation.
            const std::uint32_t w = it.weight;
            const std::uint32_t v = it.value;

            if (w > capacity)
            {
                continue;
            }

            // Iterate capacities in descending order to enforce 0/1 choice.
            for (std::size_t c = static_cast<std::size_t>(capacity); ; --c)
            {
                if (c < static_cast<std::size_t>(w))
                {
                    break;
                }

                const std::size_t idx_without = static_cast<std::size_t>(c - static_cast<std::size_t>(w));
                const std::uint32_t candidate = static_cast<std::uint32_t>(dp[idx_without] + v);

                if (candidate > dp[c])
                {
                    dp[c] = candidate;
                }

                if (c == static_cast<std::size_t>(0U))
                {
                    break;
                }
            }
        }

        return dp[static_cast<std::size_t>(capacity)];
    }
} // unnamed namespace

namespace knapsack
{

std::uint32_t maximum_value(std::uint32_t capacity, const std::vector<Item>& items)
{
    if (capacity == static_cast<std::uint32_t>(0U))
    {
        return static_cast<std::uint32_t>(0U);
    }

    const std::uint32_t result_u32 = compute_maximum_value_impl(capacity, items);
    return result_u32;
}

} // namespace knapsack

