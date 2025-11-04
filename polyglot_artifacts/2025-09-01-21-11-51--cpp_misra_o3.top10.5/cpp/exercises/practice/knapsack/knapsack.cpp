#include "knapsack.h"

#include <cstddef>   /* for std::size_t */
#include <vector>

namespace knapsack
{

[[nodiscard]] auto max_value(const std::vector<Item>& items,
                             weight_t capacity) -> value_t
{
    /*  Dynamic-programming table:
     *  dp[w] holds the best value achievable with total weight exactly w.
     */
    std::vector<value_t> dp(
        static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1U),
        static_cast<value_t>(0U));

    for (const Item& item : items)
    {
        /*  Iterate weights in descending order to avoid re-using
         *  the same item multiple times.
         */
        /*  Iterate in descending order using a signed loop counter to
         *  avoid wrap-around when w reaches zero (unsigned would under-flow).
         */
        for (std::int64_t wi = static_cast<std::int64_t>(capacity);
             wi >= static_cast<std::int64_t>(item.weight);
             --wi)
        {
            const weight_t w = static_cast<weight_t>(wi);

            const std::size_t prev_idx =
                static_cast<std::size_t>(w - item.weight);
            const std::size_t curr_idx = static_cast<std::size_t>(w);

            const value_t candidate =
                dp[prev_idx] + item.value;

            if (candidate > dp[curr_idx])
            {
                dp[curr_idx] = candidate;
            }
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

/*  Public wrapper: parameter order matches unit-test expectations. */
[[nodiscard]] auto maximum_value(weight_t capacity,
                                 const std::vector<Item>& items) -> value_t
{
    /*  Delegate to the core implementation */
    return max_value(items, capacity);
}

} // namespace knapsack

