#include "knapsack.h"
#include <cstdint>
#include <vector>

namespace knapsack
{

std::uint32_t maximum_value(std::uint32_t capacity, const std::vector<Item>& items)
{
    /* Dynamic programming table – dp[w] stores the best value achievable
       with exact total weight w */
    std::vector<std::uint32_t> dp(capacity + 1U, 0U);

    for(const Item& item : items)
    {
        /* Guard against zero-weight items to avoid an endless loop */
        if(item.weight == 0U)
        {
            continue;
        }

        /* Iterate weights in reverse to honour the 0/1 constraint
           Use an explicit check inside the loop to avoid unsigned
           wrap-around when w reaches 0. */
        for(std::uint32_t w = capacity; w > 0U; --w)
        {
            if(w < item.weight)
            {
                continue;
            }

            const std::uint32_t candidate =
                dp[w - item.weight] + item.value;

            if(dp[w] < candidate)
            {
                dp[w] = candidate;
            }
        }
    }

    return dp[capacity];
}

} // namespace knapsack

