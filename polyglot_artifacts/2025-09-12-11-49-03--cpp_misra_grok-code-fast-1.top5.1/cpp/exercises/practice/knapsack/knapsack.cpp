#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

Value maximum_value(Capacity maxWeight, const std::vector<Item>& items)
{
    if ((maxWeight < 0))
    {
        return 0;
    }
    std::size_t n = items.size();
    std::size_t W = static_cast<std::size_t>(maxWeight);
    std::vector<std::vector<Value>> dp((n + 1), std::vector<Value>((W + 1), 0));
    for (std::size_t i = 1; i <= n; ++i)
    {
        for (std::size_t w = 0; w <= W; ++w)
        {
            if ((static_cast<std::size_t>(items[(i - 1)].weight) <= w))
            {
                dp[i][w] = std::max((dp[(i - 1)][w]), (dp[(i - 1)][(w - static_cast<std::size_t>(items[(i - 1)].weight))] + items[(i - 1)].value));
            }
            else
            {
                dp[i][w] = dp[(i - 1)][w];
            }
        }
    }
    return dp[n][W];
}

} // namespace knapsack
