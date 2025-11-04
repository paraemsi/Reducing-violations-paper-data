#include "knapsack.h"

#include <algorithm>
#include <cstdint>
#include <limits>
#include <vector>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t capacity, const std::vector<Item>& items)
{
    if ((capacity) <= 0) {
        return 0;
    }

    const std::int64_t cap64 = static_cast<std::int64_t>(capacity);

    const std::size_t dp_size = static_cast<std::size_t>(cap64 + static_cast<std::int64_t>(1));
    std::vector<std::int64_t> dp(dp_size, static_cast<std::int64_t>(0));

    for (const Item& it : items) {
        if ((it.weight) <= 0) {
            continue;
        }
        const std::int64_t w = static_cast<std::int64_t>(it.weight);
        const std::int64_t v = static_cast<std::int64_t>(it.value);

        if ((w) > cap64) {
            continue;
        }

        for (std::int64_t c = cap64; (c) >= (w); --c) {
            const std::size_t ci = static_cast<std::size_t>(c);
            const std::size_t cimw = static_cast<std::size_t>(c - w);
            const std::int64_t candidate = dp[cimw] + v;
            if ((candidate) > (dp[ci])) {
                dp[ci] = candidate;
            }
        }
    }

    const std::int64_t result64 = dp[static_cast<std::size_t>(cap64)];
    if ((result64) <= static_cast<std::int64_t>(std::numeric_limits<std::int32_t>::min())) {
        return std::numeric_limits<std::int32_t>::min();
    }
    if ((result64) >= static_cast<std::int64_t>(std::numeric_limits<std::int32_t>::max())) {
        return std::numeric_limits<std::int32_t>::max();
    }
    return static_cast<std::int32_t>(result64);
}

} // namespace knapsack

