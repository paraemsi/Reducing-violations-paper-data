#include "knapsack.h"

#include <cstdint>
#include <cstddef>
#include <limits>
#include <vector>

namespace knapsack
{

auto maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items) -> std::int32_t
{
    if ((maximum_weight <= 0) || (items.empty()))
    {
        return 0;
    }

    const std::int32_t cap32 = maximum_weight;

    std::vector<std::int64_t> dp(static_cast<std::size_t>(cap32 + static_cast<std::int32_t>(1)), static_cast<std::int64_t>(0));

    for (std::size_t i = 0U; i < items.size(); ++i)
    {
        const std::int32_t w_i_raw = items[i].weight;
        const std::int32_t v_i_raw = items[i].value;

        if ((w_i_raw <= 0) || (v_i_raw <= 0))
        {
            continue;
        }

        const std::int32_t w_i = w_i_raw;
        const std::int64_t v_i = static_cast<std::int64_t>(v_i_raw);

        if (w_i > cap32)
        {
            continue;
        }

        for (std::int32_t w = cap32; (w >= w_i); --w)
        {
            const std::size_t w_idx = static_cast<std::size_t>(w);
            const std::size_t prev_idx = static_cast<std::size_t>(w - w_i);

            const std::int64_t without = dp[w_idx];
            const std::int64_t with = dp[prev_idx] + v_i;

            dp[w_idx] = ((without > with) ? without : with);
        }
    }

    const std::int64_t result64 = dp[static_cast<std::size_t>(cap32)];
    if (result64 <= static_cast<std::int64_t>(std::numeric_limits<std::int32_t>::min()))
    {
        return std::numeric_limits<std::int32_t>::min();
    }
    if (result64 >= static_cast<std::int64_t>(std::numeric_limits<std::int32_t>::max()))
    {
        return std::numeric_limits<std::int32_t>::max();
    }
    return static_cast<std::int32_t>(result64);
}

} // namespace knapsack

