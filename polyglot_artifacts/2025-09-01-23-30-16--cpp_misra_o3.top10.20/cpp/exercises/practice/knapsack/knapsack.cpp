#include "knapsack.h"

#include <cstdint>
#include <vector>

namespace knapsack
{

value_type
max_value(const std::vector<Item>& items, weight_type capacity)
{
    /* Dynamic-programming table:
       dp[w] – best value achievable with total weight exactly w.
    */
    std::vector<value_type> dp(
        static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1U),
        static_cast<value_type>(0U));

    for (const Item& item : items)
    {
        if (item.weight > capacity)
        {
            continue;
        }

        /* Traverse weights in descending order so each item is used
           at most once (0/1 knapsack).  Use signed loop variable to
           avoid wrap-around when it passes below zero. */
        for (std::int64_t w = static_cast<std::int64_t>(capacity);
             w >= static_cast<std::int64_t>(item.weight);
             --w)
        {
            const std::size_t idx      = static_cast<std::size_t>(w);
            const std::size_t prevIdx  =
                static_cast<std::size_t>(w - static_cast<std::int64_t>(item.weight));

            const value_type candidate =
                static_cast<value_type>(item.value + dp[prevIdx]);

            if (candidate > dp[idx])
            {
                dp[idx] = candidate;
            }
        }
    }

    /* The optimal solution may use less than the full capacity, so
       select the maximum value found for any permissible weight. */
    value_type best { 0U };

    for (const value_type val : dp)
    {
        if (val > best)
        {
            best = val;
        }
    }

    return best;
}

/*----------------------------------------------------------------------------*/
/* Legacy wrapper to satisfy existing tests                                   */
/*----------------------------------------------------------------------------*/
value_type
maximum_value(weight_type capacity, const std::vector<Item>& items)
{
    /* Delegate to the primary implementation that accepts (items, capacity). */
    return max_value(items, capacity);
}

} // namespace knapsack

