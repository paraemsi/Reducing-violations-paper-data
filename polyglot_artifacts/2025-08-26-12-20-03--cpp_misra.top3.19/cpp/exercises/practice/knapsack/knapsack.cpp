#include "knapsack.h"
#include <vector>
#include <cstdint>
#include <algorithm>

namespace knapsack
{

value_type maximum_value(weight_type capacity, const std::vector<Item>& items)
{
    // Use dynamic programming to solve 0/1 knapsack
    // dp[w] = max value for weight w
    std::vector<value_type> dp(static_cast<std::size_t>(capacity) + 1, static_cast<value_type>(0));

    for(const Item& item : items)
    {
        // Traverse backwards to avoid using the same item more than once
        for(weight_type w = capacity; w >= item.weight; --w)
        {
            // Parenthesize arithmetic and relational expressions per MISRA
            if(dp[static_cast<std::size_t>(w)] < (dp[static_cast<std::size_t>(w - item.weight)] + item.value))
            {
                dp[static_cast<std::size_t>(w)] = (dp[static_cast<std::size_t>(w - item.weight)] + item.value);
            }
        }
    }
    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

