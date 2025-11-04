#include "knapsack.h"

#include <vector>
#include <cstdint>

namespace knapsack
{

std::uint32_t maximum_value(std::uint32_t max_weight, const std::vector<Item>& items)
{
    std::uint32_t capacity = max_weight;

    const std::size_t cap_size = static_cast<std::size_t>(capacity);
    std::vector<std::uint32_t> dp(
        cap_size + static_cast<std::size_t>(1U),
        static_cast<std::uint32_t>(0U));

    for (std::size_t i = static_cast<std::size_t>(0U); i < items.size(); ++i)
    {
        const std::uint32_t weight = items[i].weight;
        const std::uint32_t value = items[i].value;

        if (weight == static_cast<std::uint32_t>(0U))
        {
            for (std::uint32_t w = static_cast<std::uint32_t>(0U); (w <= capacity); ++w)
            {
                dp[static_cast<std::size_t>(w)] =
                    dp[static_cast<std::size_t>(w)] + value;
            }
        }
        else if ((weight > static_cast<std::uint32_t>(0U)) && (weight <= capacity))
        {
            const std::uint32_t iterations =
                (capacity - weight) + static_cast<std::uint32_t>(1U);
            for (std::uint32_t k = static_cast<std::uint32_t>(0U); (k < iterations); ++k)
            {
                const std::uint32_t w = capacity - k;
                const std::uint32_t without_item = dp[static_cast<std::size_t>(w)];
                const std::uint32_t with_item =
                    dp[static_cast<std::size_t>(w - weight)] + value;

                if (with_item > without_item)
                {
                    dp[static_cast<std::size_t>(w)] = with_item;
                }
                else
                {
                    // no change
                }
            }
        }
        else
        {
            // ignore items with negative weight or those exceeding capacity
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

