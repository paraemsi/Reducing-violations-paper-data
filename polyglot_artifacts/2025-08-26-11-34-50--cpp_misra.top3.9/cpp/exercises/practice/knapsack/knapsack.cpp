#include "knapsack.h"
#include <vector>
#include <cstddef> // for std::size_t

namespace knapsack
{

value_type maximum_value(weight_type capacity, const std::vector<Item>& items)
{
    // Use dynamic programming: dp[w] = max value for weight w
    std::size_t n = items.size();
    std::vector<value_type> dp(static_cast<std::size_t>(capacity) + 1U, static_cast<value_type>(0));

    for(std::size_t i = 0U; i < n; ++i)
    {
        weight_type item_weight = items[i].weight;
        value_type item_value = items[i].value;
        for(weight_type w = capacity; w >= item_weight; --w)
        {
            if(dp[static_cast<std::size_t>(w)] < (dp[static_cast<std::size_t>(w - item_weight)] + item_value))
            {
                dp[static_cast<std::size_t>(w)] = (dp[static_cast<std::size_t>(w - item_weight)] + item_value);
            }
        }
    }
    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

