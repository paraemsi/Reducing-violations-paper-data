#include "knapsack.h"
#include <cstddef>
#include <vector>

namespace knapsack
{

 // Types Weight and Value are defined in knapsack.h

Value maximum_value(Weight capacity, const std::vector<Item>& items)
{
    if ((capacity <= static_cast<Weight>(0)))
    {
        return static_cast<Value>(0);
    }

    const Weight safe_capacity = ((capacity > static_cast<Weight>(0)) ? capacity : static_cast<Weight>(0));
    const std::size_t cap = static_cast<std::size_t>(safe_capacity);

    std::vector<Value> dp((cap + static_cast<std::size_t>(1U)), static_cast<Value>(0));

    for (const Item& it : items)
    {
        if ((it.weight <= static_cast<Weight>(0)))
        {
            // No action for non-positive weight items
        }
        else
        {
            const Weight w = it.weight;
            const Value v = it.value;

            for (Weight c = safe_capacity; (c >= w); --c)
            {
                const std::size_t idx_c = static_cast<std::size_t>(c);
                const std::size_t idx_c_minus_w = static_cast<std::size_t>(c - w);

                const Value candidate = static_cast<Value>(dp[idx_c_minus_w] + v);
                const Value current = dp[idx_c];

                dp[idx_c] = ((candidate > current) ? candidate : current);
            }
        }
    }

    return dp[cap];
}

} // namespace knapsack

