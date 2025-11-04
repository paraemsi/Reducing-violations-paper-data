#include "knapsack.h"

#include <cstdint>
#include <cstddef>
#include <vector>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t max_weight, const std::vector<Item>& items)
{
    if ((max_weight) <= static_cast<std::int32_t>(0)) {
        return static_cast<std::int32_t>(0);
    }

    const std::int32_t capacity_s32 = max_weight;
    const std::size_t capacity = static_cast<std::size_t>(static_cast<std::uint64_t>(capacity_s32));
    const std::size_t dp_size = static_cast<std::size_t>(capacity + static_cast<std::size_t>(1U));

    std::vector<std::int32_t> dp(dp_size, static_cast<std::int32_t>(0));

    for (std::size_t i = static_cast<std::size_t>(0U); (i < items.size()); ++i) {
        const Item& it = items[i];
        if (((it.weight) <= static_cast<std::int32_t>(0)) || ((it.value) <= static_cast<std::int32_t>(0))) {
            continue;
        }

        const std::size_t w = static_cast<std::size_t>(static_cast<std::uint64_t>(it.weight));
        const std::int32_t v = it.value;

        for (std::size_t curr = capacity; ; --curr) {
            if ((curr) < w) {
                break;
            }

            const std::size_t prev_index = static_cast<std::size_t>(curr - w);
            const std::int32_t candidate = static_cast<std::int32_t>(dp[prev_index] + v);
            if ((candidate) > dp[curr]) {
                dp[curr] = candidate;
            }

            if ((curr) == static_cast<std::size_t>(0U)) {
                break;
            }
        }
    }

    return dp[capacity];
}

} // namespace knapsack

