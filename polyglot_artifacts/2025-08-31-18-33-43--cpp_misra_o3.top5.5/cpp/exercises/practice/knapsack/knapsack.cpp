#include "knapsack.h"
#include <algorithm>
#include <vector>

namespace knapsack
{

std::vector<std::size_t> solve_knapsack(const std::vector<Item>& items,
                                        Item::weight_t capacity)
{
    const std::size_t item_count = items.size();

    /* DP table: rows = item_count + 1, cols = capacity + 1 */
    std::vector<std::vector<Item::value_t>> dp(
        item_count + 1U,
        std::vector<Item::value_t>(static_cast<std::size_t>(capacity) + 1U, 0U));

    for (std::size_t i = 1U; i <= item_count; ++i)
    {
        const Item::weight_t weight = items[i - 1U].weight;
        const Item::value_t  value  = items[i - 1U].value;

        for (Item::weight_t w = 0U; w <= capacity; ++w)
        {
            if (w >= weight)
            {
                const Item::value_t included =
                    static_cast<Item::value_t>(value + dp[i - 1U][static_cast<std::size_t>(w - weight)]);
                const Item::value_t excluded = dp[i - 1U][static_cast<std::size_t>(w)];

                dp[i][static_cast<std::size_t>(w)] =
                    (included > excluded) ? included : excluded;
            }
            else
            {
                dp[i][static_cast<std::size_t>(w)] =
                    dp[i - 1U][static_cast<std::size_t>(w)];
            }
        }
    }

    /* Reconstruct solution */
    std::vector<std::size_t> selected_indices;
    Item::weight_t w = capacity;

    for (std::size_t i = item_count; i > 0U; --i)
    {
        if (dp[i][static_cast<std::size_t>(w)] !=
            dp[i - 1U][static_cast<std::size_t>(w)])
        {
            /* Item i-1 is included */
            selected_indices.push_back(i - 1U);
            w = static_cast<Item::weight_t>(w - items[i - 1U].weight);
        }

        if (w == 0U)
        {
            break;
        }
    }

    /* Return indices in ascending order */
    std::reverse(selected_indices.begin(), selected_indices.end());

    return selected_indices;
}

Item::value_t maximum_value(Item::weight_t capacity,
                            const std::vector<Item>& items)
{
    const std::vector<std::size_t> indices = solve_knapsack(items, capacity);

    Item::value_t total_value = 0U;

    for (const std::size_t idx : indices)
    {
        total_value = static_cast<Item::value_t>(total_value + items[idx].value);
    }

    return total_value;
}

} // namespace knapsack

