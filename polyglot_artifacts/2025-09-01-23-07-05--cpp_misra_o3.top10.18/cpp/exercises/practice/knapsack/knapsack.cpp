#include "knapsack.h"
#include <vector>
#include <cstdint>
#include <cstddef>

namespace knapsack
{

value_t max_value(const std::vector<Item>& items, weight_t capacity)
{
    std::vector<value_t> dp(static_cast<std::size_t>(capacity) + 1U, static_cast<value_t>(0U));

    for(const Item& item : items)
    {
        for(weight_t w = capacity; w > static_cast<weight_t>(0U); --w)
        {
            if(w >= item.weight)
            {
                const value_t candidate = dp[static_cast<std::size_t>(w - item.weight)] + item.value;
                if((candidate > dp[static_cast<std::size_t>(w)]))
                {
                    dp[static_cast<std::size_t>(w)] = candidate;
                }
            }
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

value_t maximum_value(weight_t capacity, const std::vector<Item>& items)
{
    return max_value(items, capacity);
}

} // namespace knapsack

