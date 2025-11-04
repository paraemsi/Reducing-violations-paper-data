#include "knapsack.h"

#include <cstddef>   // std::size_t
#include <cstdint>   // std::int64_t
#include <vector>    // std::vector

namespace knapsack
{

auto maximum_value(weight_t capacity, const std::vector<Item>& items) -> value_t
{
    const std::size_t item_count{items.size()};

    /* Accumulates total value of zero-weight items (each can be taken once). */
    value_t base_value{static_cast<value_t>(0U)};

    std::vector<value_t> dp(
        static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1U),
        static_cast<value_t>(0U));

    for (std::size_t i{0U}; i < item_count; ++i)
    {
        const weight_t w{items[i].weight};
        const value_t  v{items[i].value};

        /* Zero-weight items are always taken exactly once. */
        if (w == static_cast<weight_t>(0U))
        {
            base_value =
                static_cast<value_t>(base_value + v);  /* widening, same width */
            continue;
        }

        for (std::int64_t c{static_cast<std::int64_t>(capacity)};
             c >= static_cast<std::int64_t>(w);
             --c)
        {
            const std::size_t idx{
                static_cast<std::size_t>(c)};
            const std::size_t prev_idx{
                static_cast<std::size_t>(c - static_cast<std::int64_t>(w))};

            const value_t candidate{
                dp[prev_idx] + v};

            if (candidate > dp[idx])
            {
                dp[idx] = candidate;
            }
        }
    }

    return static_cast<value_t>(
        dp[static_cast<std::size_t>(capacity)] + base_value);
}

} // namespace knapsack

