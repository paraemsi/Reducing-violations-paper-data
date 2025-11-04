#include "knapsack.h"
#include <vector>
#include <cstddef> // for std::size_t
#include <algorithm> // for std::max

namespace knapsack
{

value_type maximum_value(weight_type capacity, const std::vector<Item>& items)
{
    // Use dynamic programming: dp[w] = max value for weight w
    std::size_t n = items.size();
    std::vector<value_type> dp(static_cast<std::size_t>(capacity) + 1, static_cast<value_type>(0));

    for(std::size_t i = 0U; i < n; ++i)
    {
        for(weight_type w = capacity; w >= items[i].weight; --w)
        {
            dp[static_cast<std::size_t>(w)] = std::max(
                dp[static_cast<std::size_t>(w)],
                (dp[static_cast<std::size_t>(w - items[i].weight)] + items[i].value)
            );
        }
    }
    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

