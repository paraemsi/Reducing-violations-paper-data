#include "knapsack.h"

#include <vector> /* for dynamic array used in DP */

namespace knapsack
{

[[nodiscard]] auto max_value(const std::vector<Item>& items, std::uint32_t capacity) -> std::uint32_t
{
    /* One-dimensional dynamic-programming implementation of the 0/1 knapsack. */
    std::vector<std::uint32_t> dp(static_cast<std::size_t>(capacity) + 1U, 0U);

    for(const Item& item : items)
    {
        /* Skip zero-weight items to avoid creating an unlimited-count scenario */
        if(item.weight == 0U)
        {
            /* A zero-weight item can be taken at most once – adjust the entire
             * dp array in a forward pass and then continue with the next item. */
            for(std::uint32_t w = 0U; w <= capacity; ++w)
            {
                dp[w] = dp[w] + item.value;
            }
            continue;
        }

        /* Traverse capacities in reverse order to ensure each item is used at most once */
        for(std::uint32_t w = capacity; (w >= item.weight); --w)
        {
            std::uint32_t const candidate = dp[(w - item.weight)] + item.value;
            if((candidate > dp[w]))
            {
                dp[w] = candidate;
            }

            /* Prevent wrap-around once lowest admissible weight is processed */
            if(w == item.weight)
            {
                break;
            }
        }
    }

    return dp[capacity];
}

/* -------------------------------------------------------------------------- */
/* Public wrapper – matches the interface used by the unit tests              */
/* -------------------------------------------------------------------------- */
[[nodiscard]] auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t
{
    /* Delegate to the core implementation with (items, capacity) ordering */
    return max_value(items, capacity);
}

} // namespace knapsack

