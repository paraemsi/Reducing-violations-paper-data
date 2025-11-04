#include "knapsack.h"
#include <algorithm>   // for std::max
#include <cstddef>     // for std::size_t

namespace knapsack
{

ValueType maximum_value(WeightType capacity, const std::vector<Item>& items)
{
    /* Guard against zero capacity for early exit */
    if (capacity == static_cast<WeightType>(0U))
    {
        return static_cast<ValueType>(0U);
    }

    /* Dynamic-programming table: dp[w] holds the best value for weight w */
    std::vector<ValueType> dp(
        static_cast<std::size_t>(capacity + static_cast<WeightType>(1U)),
        static_cast<ValueType>(0U));

    for (const Item& item : items)
    {
        /* Skip items that individually exceed the capacity */
        if (item.weight > capacity)
        {
            continue;
        }

        /* Iterate weights in reverse to avoid re-using the same item twice */
        for (WeightType w = capacity; (w + static_cast<WeightType>(1U)) > item.weight; --w)
        {
            const ValueType withoutItem =
                dp[static_cast<std::size_t>(w)];
            const ValueType withItem =
                static_cast<ValueType>(dp[static_cast<std::size_t>(w - item.weight)] + item.value);

            dp[static_cast<std::size_t>(w)] =
                static_cast<ValueType>(
                    std::max(withoutItem, withItem));
        }
    }

    return dp[static_cast<std::size_t>(capacity)];
}

} // namespace knapsack

