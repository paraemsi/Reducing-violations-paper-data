#include "knapsack.h"
#include <vector>
#include <cstdint>
#include <algorithm>

namespace knapsack
{

value_t maximum_value(weight_t capacity, const std::vector<Item>& items)
{
    // Use dynamic programming: dp[w] = max value for weight w
    // All values and weights are non-negative and fit in value_t/weight_t
    std::vector<value_t> dp(static_cast<std::size_t>(capacity) + 1, static_cast<value_t>(0));

    for(const Item& item : items)
    {
        // Traverse backwards to avoid using the same item more than once
        for(weight_t w = capacity; w >= item.weight; --w)
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

