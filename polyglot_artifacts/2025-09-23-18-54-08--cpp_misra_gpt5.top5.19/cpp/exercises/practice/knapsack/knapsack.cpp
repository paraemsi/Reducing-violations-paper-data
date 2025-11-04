#include "knapsack.h"

#include <limits>
#include <stdexcept>
#include <vector>

namespace knapsack
{

Value maximum_value(Weight capacity, const std::vector<Item>& items)
{
    // Validate capacity can be represented as size_t for container sizes.
    if (static_cast<std::uint64_t>(capacity) > static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max()))
    {
        throw std::length_error("capacity too large");
    }

    const std::size_t cap = static_cast<std::size_t>(capacity);

    // Separate zero-weight items (always beneficial since values are positive).
    Value zero_weight_sum = static_cast<Value>(0U);
    std::vector<Item> positive_items;
    positive_items.reserve(items.size());
    for (std::size_t i = 0U; (i < items.size()); ++i)
    {
        const Item& it = items[i];
        if (it.weight == static_cast<Weight>(0U))
        {
            zero_weight_sum = static_cast<Value>(zero_weight_sum + it.value);
        }
        else
        {
            positive_items.push_back(it);
        }
    }

    // 1D DP over capacity for 0/1 knapsack on positive-weight items.
    std::vector<Value> dp(cap + static_cast<std::size_t>(1U), static_cast<Value>(0U));

    for (std::size_t i = 0U; (i < positive_items.size()); ++i)
    {
        const Weight wgt_raw = positive_items[i].weight;
        const Value val = positive_items[i].value;

        const std::size_t wgt = static_cast<std::size_t>(wgt_raw);

        // Descend w to ensure 0/1 (each item used at most once).
        if (wgt <= cap)
        {
            for (std::size_t w = cap; (w >= wgt); --w)
            {
                const Value with_item = static_cast<Value>(dp[w - wgt] + val);
                if (with_item > dp[w])
                {
                    dp[w] = with_item;
                }

            }
        }
        // If wgt > cap, item cannot be taken; skip.
    }

    const Value best_positive = dp[cap];
    return static_cast<Value>(best_positive + zero_weight_sum);
}

std::vector<std::size_t> optimal_selection(Weight capacity, const std::vector<Item>& items)
{
    if (static_cast<std::uint64_t>(capacity) > static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max()))
    {
        throw std::length_error("capacity too large");
    }
    const std::size_t cap = static_cast<std::size_t>(capacity);

    // Separate zero-weight items (always include) and keep their original indices.
    std::vector<std::size_t> selection;
    selection.reserve(items.size());

    std::vector<Item> positive_items;
    std::vector<std::size_t> index_map; // maps positive_items index -> original items index
    positive_items.reserve(items.size());
    index_map.reserve(items.size());

    for (std::size_t i = 0U; (i < items.size()); ++i)
    {
        const Item& it = items[i];
        if (it.weight == static_cast<Weight>(0U))
        {
            selection.push_back(i);
        }
        else
        {
            positive_items.push_back(it);
            index_map.push_back(i);
        }
    }

    if ((cap == static_cast<std::size_t>(0U)) || (positive_items.empty()))
    {
        return selection;
    }

    const std::size_t n = positive_items.size();

    // 2D DP to enable reconstruction.
    std::vector<std::vector<Value>> dp(
        n + static_cast<std::size_t>(1U),
        std::vector<Value>(cap + static_cast<std::size_t>(1U), static_cast<Value>(0U)));

    for (std::size_t i = 1U; (i <= n); ++i)
    {
        const std::size_t item_idx = i - static_cast<std::size_t>(1U);
        const std::size_t wgt = static_cast<std::size_t>(positive_items[item_idx].weight);
        const Value val = positive_items[item_idx].value;

        for (std::size_t w = 0U; (w <= cap); ++w)
        {
            // Not taking the item
            dp[i][w] = dp[i - static_cast<std::size_t>(1U)][w];

            // Taking the item if it fits
            if (w >= wgt)
            {
                const Value candidate = static_cast<Value>(dp[i - static_cast<std::size_t>(1U)][w - wgt] + val);
                if (candidate > dp[i][w])
                {
                    dp[i][w] = candidate;
                }
            }
        }
    }

    // Reconstruct chosen items.
    std::size_t w = cap;
    for (std::size_t i = n; (i > static_cast<std::size_t>(0U)); --i)
    {
        if (dp[i][w] != dp[i - static_cast<std::size_t>(1U)][w])
        {
            const std::size_t item_idx = i - static_cast<std::size_t>(1U);
            selection.push_back(index_map[item_idx]);

            const std::size_t wgt = static_cast<std::size_t>(positive_items[item_idx].weight);
            if (w >= wgt)
            {
                w = w - wgt;
            }
            else
            {
                // Should not happen, but guard to keep indices safe.
                w = static_cast<std::size_t>(0U);
            }
        }

    }

    return selection;
}

} // namespace knapsack

