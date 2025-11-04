#include "knapsack.h"
#include <cstdint>
#include <vector>

namespace knapsack
{

std::uint32_t maximum_value(std::uint32_t capacity, const std::vector<Item>& items)
{
    std::vector<std::uint32_t> dp(static_cast<std::size_t>(capacity + 1U), 0U);

    for (const Item& item : items)
    {
        if (item.weight > capacity)
        {
            continue;
        }

        std::uint32_t w = capacity;
        while (w >= item.weight)
        {
            const std::uint32_t without_item = dp[static_cast<std::size_t>(w)];
            const std::uint32_t with_item = (dp[static_cast<std::size_t>(w - item.weight)]) + item.value;

            if (with_item > without_item)
            {
                dp[static_cast<std::size_t>(w)] = with_item;
            }

            if (w == 0U)
            {
                break;
            }
            --w;
        }
    }

    return dp[capacity];
}

} // namespace knapsack

