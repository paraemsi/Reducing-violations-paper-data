#include "knapsack.h"
#include <vector>
#include <cstdint>

namespace knapsack
{

auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t
{
    /* Dynamic-programming array: dp[w] holds the best value for weight w */
    std::vector<std::uint32_t> dp(capacity + 1U, 0U);

    for (const Item& item : items)
    {
        const std::uint32_t weight = item.weight;
        const std::uint32_t value  = item.value;

        if (weight > capacity)
        {
            /* Skip items that exceed knapsack capacity */
            continue;
        }

        /* Iterate weights in descending order to avoid re-using the same item */
        std::uint32_t w = capacity;
        while (true)
        {
            if (w < weight)
            {
                break;
            }

            const std::uint32_t candidate = dp[w - weight] + value;
            if (candidate > dp[w])
            {
                dp[w] = candidate;
            }

            if (w == weight)
            {
                break;
            }
            --w;
        }
    }

    return dp[capacity];
}

} // namespace knapsack

