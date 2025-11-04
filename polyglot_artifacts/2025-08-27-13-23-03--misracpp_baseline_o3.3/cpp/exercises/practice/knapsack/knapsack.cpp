#include "knapsack.h"

#include <algorithm> // std::max
#include <cstddef>   // std::size_t
#include <vector>

namespace knapsack
{

int max_value(const std::vector<Item>& items, int max_weight)
{
    if (max_weight <= 0 || items.empty())
        return 0;

    std::vector<int> dp(static_cast<std::size_t>(max_weight) + 1, 0);

    for (const auto& item : items)
    {
        // Iterate backwards to ensure each item is only used once (0/1 knapsack).
        for (int w = max_weight; w >= item.weight; --w)
        {
            dp[static_cast<std::size_t>(w)] =
                std::max(dp[static_cast<std::size_t>(w)],
                         dp[static_cast<std::size_t>(w - item.weight)] + item.value);
        }
    }
    return dp.back();
}

int maximum_value(int max_weight, const std::vector<Item>& items)
{
    // Wrapper expected by tests – delegates to the internal implementation
    return max_value(items, max_weight);
}

std::vector<std::size_t> select_items(const std::vector<Item>& items,
                                      int max_weight)
{
    const std::size_t n = items.size();
    if (n == 0 || max_weight <= 0)
        return {};

    // dp[i][w] – best value using first i items and capacity w
    std::vector<std::vector<int>> dp(
        n + 1, std::vector<int>(static_cast<std::size_t>(max_weight) + 1, 0));

    // Build table
    for (std::size_t i = 1; i <= n; ++i)
    {
        int wt = items[i - 1].weight;
        int val = items[i - 1].value;
        for (int w = 0; w <= max_weight; ++w)
        {
            dp[i][static_cast<std::size_t>(w)] = dp[i - 1][static_cast<std::size_t>(w)];
            if (w >= wt)
            {
                dp[i][static_cast<std::size_t>(w)] =
                    std::max(dp[i][static_cast<std::size_t>(w)],
                             dp[i - 1][static_cast<std::size_t>(w - wt)] + val);
            }
        }
    }

    // Backtrack to find chosen items
    std::vector<std::size_t> chosen;
    int w = max_weight;
    for (std::size_t i = n; i > 0; --i)
    {
        if (dp[i][static_cast<std::size_t>(w)] !=
            dp[i - 1][static_cast<std::size_t>(w)])
        {
            // item i-1 is included
            chosen.push_back(i - 1);
            w -= items[i - 1].weight;
        }
    }
    std::reverse(chosen.begin(), chosen.end());
    return chosen;
}

} // namespace knapsack

