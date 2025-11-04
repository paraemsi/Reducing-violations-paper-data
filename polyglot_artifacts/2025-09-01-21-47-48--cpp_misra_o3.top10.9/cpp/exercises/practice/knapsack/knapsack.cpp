#include "knapsack.h"

#include <algorithm>
#include <cstdint>
#include <vector>

namespace knapsack
{

value_t maximum_value(const weight_t capacity, const std::vector<Item>& items)
{
    /* Dynamic-programming array where dp[w] holds the best value for weight w */
    std::vector<value_t> dp(static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1U),
                            static_cast<value_t>(0U));

    for (const Item& itm : items)
    {
        const weight_t wt  = itm.weight;
        const value_t  val = itm.value;

        using idx_t = std::int64_t;

        /* Iterate weights in reverse to avoid re-using the same item */
        for (idx_t cap = static_cast<idx_t>(capacity);
             cap >= static_cast<idx_t>(wt);
             --cap)
        {
            const std::size_t cap_idx  = static_cast<std::size_t>(cap);
            const std::size_t prev_idx = static_cast<std::size_t>(cap - static_cast<idx_t>(wt));

            const value_t candidate = static_cast<value_t>((dp[prev_idx] + val));

            if (candidate > dp[cap_idx])
            {
                dp[cap_idx] = candidate;
            }

            if (cap == static_cast<idx_t>(wt)) /* prevent unsigned wrap-around */
            {
                break;
            }
        }
    }

    return dp.back();
}

} // namespace knapsack

