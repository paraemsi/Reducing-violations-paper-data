#include "knapsack.h"
#include <algorithm>
#include <cstddef>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty())
    {
        return 0;
    }

    std::vector<int> dp(static_cast<std::size_t>(capacity + 1), 0);
    for (const auto& it : items)
    {
        for (int w = capacity; w >= it.weight; --w)
        {
            dp[static_cast<std::size_t>(w)] =
                std::max(dp[static_cast<std::size_t>(w)],
                         dp[static_cast<std::size_t>(w - it.weight)] + it.value);
        }
    }
    return dp[static_cast<std::size_t>(capacity)];
}

int maximum_value(const std::vector<Item>& items, int capacity)
{
    return maximum_value(capacity, items);
}

std::vector<Item> optimal_items(int capacity, const std::vector<Item>& items)
{
    std::vector<Item> selected;
    if (capacity <= 0 || items.empty())
    {
        return selected;
    }

    const std::size_t n = items.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(static_cast<std::size_t>(capacity + 1), 0));

    for (std::size_t i = 1; i <= n; ++i)
    {
        const int wt = items[i - 1].weight;
        const int val = items[i - 1].value;
        for (int w = 0; w <= capacity; ++w)
        {
            dp[i][static_cast<std::size_t>(w)] = dp[i - 1][static_cast<std::size_t>(w)];
            if (wt <= w)
            {
                dp[i][static_cast<std::size_t>(w)] =
                    std::max(dp[i][static_cast<std::size_t>(w)],
                             dp[i - 1][static_cast<std::size_t>(w - wt)] + val);
            }
        }
    }

    int w = capacity;
    for (std::size_t i = n; i-- > 0;)
    {
        if (dp[i + 1][static_cast<std::size_t>(w)] != dp[i][static_cast<std::size_t>(w)])
        {
            selected.push_back(items[i]);
            w -= items[i].weight;
            if (w <= 0)
            {
                break;
            }
        }
    }

    std::reverse(selected.begin(), selected.end());
    return selected;
}

} // namespace knapsack

