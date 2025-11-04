#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstddef>
#include <cstdint>

namespace knapsack
{

auto solve(const std::vector<Item>& items, std::uint32_t capacity) -> Result
{
    const std::size_t n = items.size();

    std::vector<std::vector<std::uint32_t>> dp(
        n + 1U,
        std::vector<std::uint32_t>(static_cast<std::size_t>(capacity) + 1U, 0U));

    std::vector<std::vector<bool>> keep(
        n,
        std::vector<bool>(static_cast<std::size_t>(capacity) + 1U, false));

    for (std::size_t i = 0U; i < n; ++i)
    {
        for (std::uint32_t w = 0U; w <= capacity; ++w)
        {
            const std::size_t   w_idx    = static_cast<std::size_t>(w);
            const std::uint32_t not_take = dp[i][w_idx];
            std::uint32_t       take     = 0U;

            if ((items[i].weight) <= w)
            {
                take =
                    (items[i].value) + dp[i][w_idx - static_cast<std::size_t>(items[i].weight)];
            }

            if (take > not_take)
            {
                dp[i + 1U][w_idx] = take;
                keep[i][w_idx]    = true;
            }
            else
            {
                dp[i + 1U][w_idx] = not_take;
            }
        }
    }

    Result result{};
    result.max_value = dp[n][static_cast<std::size_t>(capacity)];

    std::uint32_t w = capacity;
    for (std::size_t i = n; i > 0U; --i)
    {
        if ((keep[i - 1U][static_cast<std::size_t>(w)]) == true)
        {
            result.selected_indices.push_back(i - 1U);
            w = w - (items[i - 1U].weight);
        }
    }

    std::reverse(result.selected_indices.begin(), result.selected_indices.end());

    return result;
}

auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t
{
    return solve(items, capacity).max_value;
}

} // namespace knapsack

