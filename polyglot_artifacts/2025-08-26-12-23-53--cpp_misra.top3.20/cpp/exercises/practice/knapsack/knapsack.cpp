#include "knapsack.h"
#include <vector>
#include <cstddef> // for std::size_t
#include <algorithm> // for std::max

namespace knapsack
{

value_t maximum_value(weight_t capacity, const std::vector<Item>& items)
{
    std::vector<value_t> dp(static_cast<std::size_t>(capacity) + 1, static_cast<value_t>(0));

    for(const Item& item : items)
    {
        for(weight_t w = capacity; w >= item.weight; --w)
        {
            dp[static_cast<std::size_t>(w)] = std::max(
                dp[static_cast<std::size_t>(w)],
                (dp[static_cast<std::size_t>(w - item.weight)] + item.value)
            );
        }
    }
    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

