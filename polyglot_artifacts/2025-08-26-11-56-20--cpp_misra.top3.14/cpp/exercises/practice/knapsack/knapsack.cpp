#include "knapsack.h"
#include <vector>
#include <cstddef> // for std::size_t
#include <algorithm> // for std::max

namespace knapsack
{

value_type maximum_value(weight_type capacity, const std::vector<Item>& items)
{
    // Use dynamic programming: dp[w] = max value for weight w
    // All values and weights are non-negative and fit in value_type/weight_type
    std::size_t n = items.size();
    std::vector<value_type> dp(static_cast<std::size_t>(capacity) + 1, static_cast<value_type>(0));

    for(std::size_t i = 0U; i < n; ++i)
    {
        weight_type item_weight = items[i].weight;
        value_type item_value = items[i].value;
        // Traverse backwards to avoid using the same item more than once
        for(weight_type w = capacity; w >= item_weight; --w)
        {
            // Parenthesize arithmetic and relational expressions per MISRA
            if(dp[static_cast<std::size_t>(w)] < (dp[static_cast<std::size_t>(w - item_weight)] + item_value))
            {
                dp[static_cast<std::size_t>(w)] = (dp[static_cast<std::size_t>(w - item_weight)] + item_value);
            }
        }
    }
    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

