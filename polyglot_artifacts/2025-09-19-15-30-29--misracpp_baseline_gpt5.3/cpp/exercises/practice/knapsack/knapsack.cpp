#include "knapsack.h"

namespace knapsack
{

int maximum_value(int max_weight, const std::vector<Item>& items)
{
    if (max_weight <= 0 || items.empty())
    {
        return 0;
    }

    std::vector<int> dp(max_weight + 1, 0);

    for (const auto& item : items)
    {
        int w = item.weight;
        int v = item.value;

        if (w < 0)
        {
            continue; // ignore items with negative weight
        }

        for (int cap = max_weight; cap >= w; --cap)
        {
            int with_item = dp[cap - w] + v;
            if (with_item > dp[cap])
            {
                dp[cap] = with_item;
            }
        }
    }

    return dp[max_weight];
}

} // namespace knapsack

