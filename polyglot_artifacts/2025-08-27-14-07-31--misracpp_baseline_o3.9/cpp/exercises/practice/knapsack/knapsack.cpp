#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int max_weight, const std::vector<Item>& items)
{
    const std::size_t n = items.size();
    if (max_weight <= 0 || n == 0)
        return 0;

    // 1-D DP: dp[w] holds best value using capacity w
    std::vector<int> dp(max_weight + 1, 0);

    for (const auto& item : items)
    {
        // iterate downward to ensure each item chosen at most once
        for (int w = max_weight; w >= item.weight; --w)
        {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }

    return *std::max_element(dp.begin(), dp.end());
}

std::vector<std::size_t> select_items(const std::vector<Item>& items, int max_weight)
{
    const std::size_t n = items.size();
    if (max_weight <= 0 || n == 0)
        return {};

    // 2-dimensional DP where
    // dp[i][w] = maximum value achievable using the first i items
    //            with an exact capacity of w.
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(max_weight + 1, 0));

    for (std::size_t i = 1; i <= n; ++i)
    {
        const int wt  = items[i - 1].weight;
        const int val = items[i - 1].value;

        for (int w = 0; w <= max_weight; ++w)
        {
            if (wt <= w)
            {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - wt] + val);
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Reconstruct chosen item indices
    std::vector<std::size_t> chosen;
    int w = max_weight;
    for (std::size_t i = n; i > 0 && w > 0; --i)
    {
        if (dp[i][w] != dp[i - 1][w])
        {
            chosen.push_back(i - 1);          // item (i-1) was chosen
            w -= items[i - 1].weight;
        }
    }

    std::reverse(chosen.begin(), chosen.end());
    return chosen;
}

} // namespace knapsack

