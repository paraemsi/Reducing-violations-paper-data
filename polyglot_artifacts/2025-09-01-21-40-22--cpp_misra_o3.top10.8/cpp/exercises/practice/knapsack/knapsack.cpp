#include "knapsack.h"

#include <algorithm>

namespace knapsack
{

auto max_value(const std::vector<Item>& items, std::uint32_t capacity) -> std::uint32_t
{
    const std::size_t cap_size = static_cast<std::size_t>(capacity);
    std::vector<std::uint32_t> dp(cap_size + static_cast<std::size_t>(1U), static_cast<std::uint32_t>(0U));

    for (const Item& item : items)
    {
        for (std::int64_t w = static_cast<std::int64_t>(capacity);
             w >= static_cast<std::int64_t>(item.weight);
             --w)
        {
            const std::size_t idx = static_cast<std::size_t>(w);
            const std::size_t with_idx = idx - static_cast<std::size_t>(item.weight);

            const std::uint32_t candidate = dp[with_idx] + item.value;

            if (candidate > dp[idx])
            {
                dp[idx] = candidate;
            }
        }
    }

    return dp[cap_size];
}

auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t
{
    /* wrapper to satisfy external interface expectations */
    return max_value(items, capacity);
}

} // namespace knapsack

