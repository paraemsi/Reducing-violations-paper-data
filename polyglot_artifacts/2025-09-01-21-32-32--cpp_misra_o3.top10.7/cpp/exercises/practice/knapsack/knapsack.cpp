#include "knapsack.h"
#include <algorithm>   /* for std::reverse */
#include <cstddef>     /* for std::size_t */
#include <vector>

namespace knapsack
{

auto solve(const std::vector<Item>& items, u32 capacity) noexcept -> Result
{
    const std::size_t item_count = items.size();

    std::vector<std::vector<u32>> dp(
        item_count + 1U,
        std::vector<u32>(static_cast<std::size_t>(capacity) + 1U, 0U));

    std::vector<std::vector<bool>> keep(
        item_count + 1U,
        std::vector<bool>(static_cast<std::size_t>(capacity) + 1U, false));

    for (std::size_t i = 1U; i <= item_count; ++i)
    {
        const u32 wt  = items[i - 1U].weight;
        const u32 val = items[i - 1U].value;

        for (u32 w = 0U; w <= capacity; ++w)
        {
            if ((wt <= w))
            {
                const u32 val_with =
                    val + dp[i - 1U][static_cast<std::size_t>(w - wt)];
                const u32 val_without =
                    dp[i - 1U][static_cast<std::size_t>(w)];

                if ((val_with > val_without))
                {
                    dp[i][static_cast<std::size_t>(w)]   = val_with;
                    keep[i][static_cast<std::size_t>(w)] = true;
                }
                else
                {
                    dp[i][static_cast<std::size_t>(w)] = val_without;
                }
            }
            else
            {
                dp[i][static_cast<std::size_t>(w)] =
                    dp[i - 1U][static_cast<std::size_t>(w)];
            }
        }
    }

    std::vector<std::size_t> indices;
    indices.reserve(item_count);

    u32 w = capacity;
    for (std::size_t i = item_count; i > 0U; --i)
    {
        if (keep[i][static_cast<std::size_t>(w)])
        {
            indices.push_back(i - 1U);
            w -= items[i - 1U].weight;
        }
    }

    std::reverse(indices.begin(), indices.end());

    const u32 total_value =
        dp[item_count][static_cast<std::size_t>(capacity)];

    return Result{total_value, indices};
}

/* ------------------------------------------------------------- */
/* Convenience helper returning only maximum value.              */
/* ------------------------------------------------------------- */
auto maximum_value(u32 capacity, const std::vector<Item>& items) noexcept -> u32
{
    /* Delegate to solve for full result. */
    const Result res = solve(items, capacity);
    return res.total_value;
}

} // namespace knapsack

