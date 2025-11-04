#include "knapsack.h"

namespace knapsack
{

value_type maximum_value(capacity_type capacity, const std::vector<Item>& items)
{
    /* Dynamic programming table: dp[w] holds the best value for weight w */
    std::vector<value_type> dp(static_cast<std::size_t>(capacity) + 1U,
                               static_cast<value_type>(0U));

    for (const Item& it : items)
    {
        if (it.weight > capacity)
        {
            /* Item cannot fit at all */
            continue;
        }

        /* Iterate weights backwards to ensure each item is taken at most once */
        for (capacity_type w = capacity; (w >= it.weight); --w)
        {
            const capacity_type prev_index = static_cast<capacity_type>(w - it.weight);
            const value_type candidate_value =
                dp[static_cast<std::size_t>(prev_index)] + it.value;

            if ((candidate_value > dp[static_cast<std::size_t>(w)]))
            {
                dp[static_cast<std::size_t>(w)] = candidate_value;
            }

            if (w == it.weight)
            {
                /* Prevent wrap-around of unsigned loop variable */
                break;
            }
        }
    }

    return dp.back();
}

} // namespace knapsack

