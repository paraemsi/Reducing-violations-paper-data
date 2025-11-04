#include "knapsack.h"

#include <algorithm>   // std::max
#include <vector>

namespace knapsack
{

auto maximum_value(std::uint32_t            capacity,
                   const std::vector<Item>& items) -> std::uint32_t
{
    /* 1-D dynamic-programming table: dp[w] = best value for weight w */
    std::vector<std::uint32_t> dp(capacity + static_cast<std::uint32_t>(1U),
                                  static_cast<std::uint32_t>(0U));

    for (const Item& item : items)
    {
        /*  Ignore zero-weight items. They would otherwise trigger an
         *  endless loop in the reverse-weight traversal and, if their
         *  value were positive, enable unbounded knapsack value.        */
        if (item.weight == static_cast<std::uint32_t>(0U))
        {
            /* Unique zero-weight item: add its value once to every entry.   */
            for (std::uint32_t &cell : dp)
            {
                cell = static_cast<std::uint32_t>(
                    cell + item.value);
            }
            continue;
        }

        /*  Iterate weights in reverse so each item is used at most once  */
        for (std::int32_t w = static_cast<std::int32_t>(capacity);
             w >= static_cast<std::int32_t>(item.weight);
             --w)
        {
            const std::uint32_t uw = static_cast<std::uint32_t>(w);
            dp[uw] = std::max(dp[uw],
                              static_cast<std::uint32_t>(
                                  dp[uw - item.weight] + item.value));
        }
        /*  NOTE: loop body above uses a signed loop variable to
         *  prevent unsigned under-flow when the counter crosses 0. */
    }

    return dp[capacity];
}

auto select_items(std::uint32_t            capacity,
                  const std::vector<Item>& items) -> std::vector<std::size_t>
{
    const std::size_t item_count = items.size();

    /* 2-D DP table to enable reconstruction of solution */
    std::vector<std::vector<std::uint32_t>> dp(item_count + static_cast<std::size_t>(1U),
                                               std::vector<std::uint32_t>(capacity + static_cast<std::uint32_t>(1U),
                                                                          static_cast<std::uint32_t>(0U)));

    for (std::size_t i = static_cast<std::size_t>(1U); i <= item_count; ++i)
    {
        const Item& itm = items[i - static_cast<std::size_t>(1U)];

        for (std::uint32_t w = static_cast<std::uint32_t>(0U); w <= capacity; ++w)
        {
            if (w < itm.weight)
            {
                dp[i][w] = dp[i - static_cast<std::size_t>(1U)][w];
            }
            else
            {
                const std::uint32_t without_item =
                    dp[i - static_cast<std::size_t>(1U)][w];
                const std::uint32_t with_item =
                    dp[i - static_cast<std::size_t>(1U)][(w - itm.weight)] + itm.value;

                dp[i][w] = (with_item > without_item) ? with_item : without_item;
            }
        }
    }

    /* Back-track to find which items were selected */
    std::vector<std::size_t> selected;
    std::uint32_t            w = capacity;

    for (std::size_t i = item_count; i > static_cast<std::size_t>(0U); --i)
    {
        if (dp[i][w] != dp[i - static_cast<std::size_t>(1U)][w])
        {
            selected.push_back(i - static_cast<std::size_t>(1U));
            w = static_cast<std::uint32_t>(
                w - items[i - static_cast<std::size_t>(1U)].weight);
        }

        if (w == static_cast<std::uint32_t>(0U))
        {
            break; /* capacity exhausted */
        }
    }

    std::reverse(selected.begin(), selected.end());
    return selected;
}

} // namespace knapsack

