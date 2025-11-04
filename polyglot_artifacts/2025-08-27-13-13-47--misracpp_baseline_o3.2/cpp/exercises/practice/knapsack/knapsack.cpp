#include "knapsack.h"

#include <algorithm>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty())
        return 0;

    // 1-dimensional DP array: dp[w] == best value for weight w
    std::vector<int> dp(static_cast<std::size_t>(capacity) + 1, 0);

    for (const auto& item : items)
    {
        // iterate backwards so each item is used at most once (0/1 knapsack)
        for (int w = capacity; w >= item.weight; --w)
        {
            dp[static_cast<std::size_t>(w)] = std::max(
                dp[static_cast<std::size_t>(w)],
                dp[static_cast<std::size_t>(w - item.weight)] + item.value);
        }
    }
    return dp.back();
}

std::vector<std::size_t> optimal_item_indices(int capacity,
                                              const std::vector<Item>& items)
{
    const std::size_t n = items.size();
    if (n == 0 || capacity <= 0)
        return {};

    // Full 2-D DP table for backtracking
    std::vector<std::vector<int>> dp(
        n + 1, std::vector<int>(static_cast<std::size_t>(capacity) + 1, 0));

    for (std::size_t i = 1; i <= n; ++i)
    {
        int wt = items[i - 1].weight;
        int val = items[i - 1].value;
        for (int w = 0; w <= capacity; ++w)
        {
            dp[i][static_cast<std::size_t>(w)] = dp[i - 1][static_cast<std::size_t>(w)];
            if (wt <= w)
            {
                dp[i][static_cast<std::size_t>(w)] = std::max(
                    dp[i][static_cast<std::size_t>(w)],
                    dp[i - 1][static_cast<std::size_t>(w - wt)] + val);
            }
        }
    }

    // Back-track to find which items were chosen
    std::vector<std::size_t> indices;
    int w = capacity;
    for (std::size_t i = n; i > 0; --i)
    {
        if (dp[i][static_cast<std::size_t>(w)] != dp[i - 1][static_cast<std::size_t>(w)])
        {
            indices.push_back(i - 1);          // item i-1 was taken
            w -= items[i - 1].weight;
            if (w == 0)
                break;
        }
    }
    std::reverse(indices.begin(), indices.end());
    return indices;
}

} // namespace knapsack

