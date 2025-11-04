#include "knapsack.h"
#include <cstddef>

namespace knapsack
{

auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t
{
    const std::size_t cap_size = static_cast<std::size_t>(capacity);
    std::vector<std::uint32_t> dp(
        static_cast<std::size_t>(cap_size + static_cast<std::size_t>(1U)),
        static_cast<std::uint32_t>(0U)
    );
    std::uint32_t zero_weight_bonus = static_cast<std::uint32_t>(0U);

    for (const Item& it : items)
    {
        if ((it.value == static_cast<std::uint32_t>(0U)))
        {
            continue;
        }
        if ((it.weight == static_cast<std::uint32_t>(0U)))
        {
            zero_weight_bonus = static_cast<std::uint32_t>(zero_weight_bonus + it.value);
            continue;
        }

        const std::size_t wt_size = static_cast<std::size_t>(it.weight);
        if ((cap_size >= wt_size))
        {
            std::size_t w = cap_size;
            for (;;)
            {
                const std::size_t idx = w;
                const std::size_t prev_idx = static_cast<std::size_t>(idx - wt_size);
                const std::uint32_t candidate = static_cast<std::uint32_t>(dp[prev_idx] + it.value);

                if ((dp[idx] < candidate))
                {
                    dp[idx] = candidate;
                }

                if (w == wt_size)
                {
                    break;
                }
                --w;
            }
        }
    }

    return dp[cap_size] + zero_weight_bonus;
}

} // namespace knapsack

