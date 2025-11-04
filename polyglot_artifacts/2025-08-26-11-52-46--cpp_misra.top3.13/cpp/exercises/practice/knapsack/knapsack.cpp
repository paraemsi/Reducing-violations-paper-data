#include "knapsack.h"
#include <vector>
#include <cstddef> // for std::size_t
#include <algorithm> // for std::max

namespace knapsack
{

value_type maximum_value(weight_type capacity, const std::vector<Item>& items)
{
    // Use dynamic programming: dp[w] = max value for weight w
    std::vector<value_type> dp(static_cast<std::size_t>(capacity) + 1, static_cast<value_type>(0));

    for(const Item& item : items)
    {
        for(weight_type w = capacity; w >= item.weight; --w)
        {
            value_type candidate = (dp[static_cast<std::size_t>(w - item.weight)] + item.value);
            if(dp[static_cast<std::size_t>(w)] < candidate)
            {
                dp[static_cast<std::size_t>(w)] = candidate;
            }
        }
    }
    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

