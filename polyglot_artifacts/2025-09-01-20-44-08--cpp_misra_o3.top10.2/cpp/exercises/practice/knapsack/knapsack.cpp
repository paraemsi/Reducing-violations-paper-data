#include "knapsack.h"

#include <vector>
#include <cstddef>

namespace knapsack
{

auto max_value(const std::vector<Item>& items,
               std::uint32_t           capacity) -> std::uint32_t
{
    /* 0-1 knapsack solved with a one-dimensional DP table.
       dp[w] keeps the best value achievable with total weight exactly w. */
    const std::size_t table_size =
        (static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1U));
    std::vector<std::uint32_t> dp(
        table_size,
        static_cast<std::uint32_t>(0U));

    for(const Item& item : items)
    {
        if((item.weight > capacity) || (item.weight == static_cast<std::uint32_t>(0U)))
        {
            continue;
        }

        /* Iterate weights in descending order so every item is used at most once */
        std::uint32_t w_index = capacity;
        while(w_index >= item.weight)
        {
            const std::uint32_t candidate =
                (dp[static_cast<std::size_t>(w_index - item.weight)] + item.value);

            if(candidate > dp[static_cast<std::size_t>(w_index)])
            {
                dp[static_cast<std::size_t>(w_index)] = candidate;
            }

            if(w_index == item.weight)
            {
                break;
            }
            --w_index;
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

auto maximum_value(std::uint32_t           capacity,
                   const std::vector<Item>& items) -> std::uint32_t
{
    /* Forward to the internal implementation keeping MISRA rules intact. */
    return max_value(items, capacity);
}

} // namespace knapsack

