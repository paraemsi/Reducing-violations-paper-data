#include "knapsack.h"

#include <cstddef>
#include <vector>

namespace knapsack
{

[[nodiscard]] std::uint32_t maximum_value(std::uint32_t capacity, const std::vector<Item>& items)
{
    const std::size_t cap { static_cast<std::size_t>(capacity) };

    std::vector<std::uint32_t> dp(cap + static_cast<std::size_t>(1U),
                                  static_cast<std::uint32_t>(0U));

    for (const Item& item : items)
    {
        const std::size_t weight_sz { static_cast<std::size_t>(item.weight) };

        /* Iterate backwards so each item is only considered once. */
        for (std::size_t w { cap };
             ((w + static_cast<std::size_t>(1U)) > weight_sz); --w)
        {
            const std::uint32_t without_item { dp[w] };
            const std::uint32_t with_item {
                dp[w - weight_sz] + item.value
            };

            if (with_item > without_item)
            {
                dp[w] = with_item;
            }
        }
    }

    return dp[cap];
}

} // namespace knapsack

