#include "knapsack.h"
#include <algorithm>
#include <cstddef>
#include <vector>

namespace knapsack
{

[[nodiscard]] auto max_value(const std::vector<Item>& items, std::uint32_t capacity) -> std::uint32_t
{
    /* Dynamic-programming array where index = current capacity */
    std::vector<std::uint32_t> dp(
        static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1U),
        static_cast<std::uint32_t>(0U));

    for (const Item& item : items)
    {
        const std::uint32_t weight = item.weight;
        const std::uint32_t value  = item.value;

        /* Ignore items with zero weight or weight above the knapsack limit */
        if ((weight == static_cast<std::uint32_t>(0U)) || (weight > capacity))
        {
            continue;
        }

        /* Traverse capacities backwards so each item is used at most once */
        for (std::uint32_t w = capacity; w >= weight; --w)
        {
            const std::uint32_t candidate =
                dp[static_cast<std::size_t>(w - weight)] + value;

            if (candidate > dp[static_cast<std::size_t>(w)])
            {
                dp[static_cast<std::size_t>(w)] = candidate;
            }

            if (w == static_cast<std::uint32_t>(0U))
            {
                break; /* Prevent unsigned wrap-around */
            }
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

[[nodiscard]] auto optimal_selection(const std::vector<Item>& items,
                       std::uint32_t             capacity) -> std::vector<std::size_t>
{
    const std::size_t item_count = items.size();

    /* 2-D DP table for reconstruction of the chosen items */
    std::vector<std::vector<std::uint32_t>> dp(
        item_count + static_cast<std::size_t>(1U),
        std::vector<std::uint32_t>(
            static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1U),
            static_cast<std::uint32_t>(0U)));

    for (std::size_t i = static_cast<std::size_t>(1U); i <= item_count; ++i)
    {
        const std::uint32_t weight = items[i - static_cast<std::size_t>(1U)].weight;
        const std::uint32_t value  = items[i - static_cast<std::size_t>(1U)].value;

        for (std::uint32_t w = static_cast<std::uint32_t>(0U); w <= capacity; ++w)
        {
            if (w < weight)
            {
                dp[i][static_cast<std::size_t>(w)] =
                    dp[i - static_cast<std::size_t>(1U)][static_cast<std::size_t>(w)];
            }
            else
            {
                const std::uint32_t without_item =
                    dp[i - static_cast<std::size_t>(1U)][static_cast<std::size_t>(w)];
                const std::uint32_t with_item =
                    dp[i - static_cast<std::size_t>(1U)]
                      [static_cast<std::size_t>(w - weight)] +
                    value;

                dp[i][static_cast<std::size_t>(w)] =
                    (with_item > without_item) ? with_item : without_item;
            }
        }
    }

    /* Reconstruct the set of chosen item indices */
    std::vector<std::size_t> selection;
    std::uint32_t           remaining_capacity = capacity;

    for (std::size_t i = item_count; i > static_cast<std::size_t>(0U); --i)
    {
        if (dp[i][static_cast<std::size_t>(remaining_capacity)] !=
            dp[i - static_cast<std::size_t>(1U)]
               [static_cast<std::size_t>(remaining_capacity)])
        {
            selection.push_back(i - static_cast<std::size_t>(1U));
            remaining_capacity -=
                items[i - static_cast<std::size_t>(1U)].weight;

            if (remaining_capacity == static_cast<std::uint32_t>(0U))
            {
                break;
            }
        }
    }

    std::reverse(selection.begin(), selection.end());
    return selection;
}

[[nodiscard]] auto maximum_value(std::uint32_t capacity,
                                 const std::vector<Item>& items) -> std::uint32_t
{
    return max_value(items, capacity);
}

} // namespace knapsack

