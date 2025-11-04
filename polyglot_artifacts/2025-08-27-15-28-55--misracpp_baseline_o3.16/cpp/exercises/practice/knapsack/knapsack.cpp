#include "knapsack.h"
#include <algorithm>

namespace knapsack
{

int max_value(const std::vector<Item>& items, int max_weight)
{
    if (max_weight <= 0 || items.empty())
        return 0;

    std::vector<int> dp(max_weight + 1, 0);

    for (const auto& item : items)
    {
        for (int w = max_weight; w >= item.weight; --w)
        {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }
    return dp[max_weight];
}

int maximum_value(int max_weight, const std::vector<Item>& items)
{
    // Adapter: tests expect (capacity, items) parameter order
    return max_value(items, max_weight);
}

std::vector<std::size_t> optimal_item_indices(const std::vector<Item>& items, int max_weight)
{
    const std::size_t n = items.size();
    if (n == 0 || max_weight <= 0)
        return {};

    // 2-D DP table where dp[i][w] is the best value using
    // the first i items and weight limit w.
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(max_weight + 1, 0));

    for (std::size_t i = 1; i <= n; ++i)
    {
        for (int w = 0; w <= max_weight; ++w)
        {
            dp[i][w] = dp[i - 1][w]; // skip current item
            if (items[i - 1].weight <= w)
            {
                dp[i][w] = std::max(
                    dp[i][w],
                    dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
        }
    }

    // Reconstruct chosen item indices.
    std::vector<std::size_t> indices;
    int w = max_weight;
    // Traverse items in reverse (zero-based index) to find which were taken.
    for (int i = static_cast<int>(n) - 1; i >= 0 && w > 0; --i)
    {
        if (dp[i + 1][w] != dp[i][w]) // value differs ⇒ item i was chosen
        {
            indices.push_back(static_cast<std::size_t>(i));
            w -= items[i].weight;
        }
    }
    std::reverse(indices.begin(), indices.end());
    return indices;
}

} // namespace knapsack

