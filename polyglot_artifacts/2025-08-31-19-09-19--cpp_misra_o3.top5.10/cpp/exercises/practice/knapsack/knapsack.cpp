#include "knapsack.h"
#include <vector>

namespace knapsack
{

auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t
{
    /* Vector index uses std::size_t, convert explicitly to respect MISRA rules */
    const std::size_t cap_size = static_cast<std::size_t>(capacity);
    std::vector<std::uint32_t> dp(cap_size + 1U, 0U);

    /* Iterate over each item (0-1 knapsack, reverse loop on capacity) */
    for (const Item& item : items)
    {
        const std::uint32_t weight = item.weight;
        const std::uint32_t value  = item.value;

        /* Skip zero-weight items to prevent an endless loop in the
         * reverse-iteration that follows. A zero-weight, positive-value
         * item would make the optimal value unbounded anyway. */
        if (weight == 0U)
        {
            continue;
        }

        for (std::size_t c = cap_size; c >= static_cast<std::size_t>(weight); --c)
        {
            const std::uint32_t candidate =
                dp[(c - static_cast<std::size_t>(weight))] + value;

            if (candidate > dp[c])
            {
                dp[c] = candidate;
            }

            if (c == 0U)
            {
                /* Prevent underflow when c is unsigned */
                break;
            }
        }
    }

    return dp[cap_size];
}

} // namespace knapsack

