#include "knapsack.h"
#include <vector>
#include <cstdint>

namespace knapsack
{

std::uint32_t knapsack_max_value(const std::vector<Item>& items,
                                 std::uint32_t maxWeight)
{
    std::vector<std::uint32_t> dp(static_cast<std::size_t>(maxWeight) + static_cast<std::size_t>(1U),
                                  static_cast<std::uint32_t>(0U));

    for (const Item& item : items)
    {
        for (std::int32_t w = static_cast<std::int32_t>(maxWeight);
             w >= static_cast<std::int32_t>(item.weight);
             --w)
        {
            const std::uint32_t index =
                static_cast<std::uint32_t>(w);
            const std::uint32_t prevIndex =
                static_cast<std::uint32_t>(
                    w - static_cast<std::int32_t>(item.weight));

            const std::uint32_t candidate =
                dp[static_cast<std::size_t>(prevIndex)] + item.value;

            if (candidate > dp[static_cast<std::size_t>(index)])
            {
                dp[static_cast<std::size_t>(index)] = candidate;
            }
        }
    }

    return dp[static_cast<std::size_t>(maxWeight)];
}

std::uint32_t maximum_value(std::uint32_t maxWeight,
                            const std::vector<Item>& items)
{
    return knapsack_max_value(items, maxWeight);
}

} // namespace knapsack

