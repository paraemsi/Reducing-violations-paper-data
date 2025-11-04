#include "knapsack.h"

#include <cstddef>
#include <vector>

namespace knapsack
{

Value maximum_value(Weight capacity, const std::vector<Item>& items)
{
    const std::size_t cap_size = static_cast<std::size_t>(capacity);
    std::vector<Value> dp((cap_size + static_cast<std::size_t>(1U)), static_cast<Value>(0U));
    std::vector<Value> prev = dp;

    for (const Item& it : items)
    {
        prev = dp;

        const std::size_t wgt = static_cast<std::size_t>(it.weight);
        for (std::size_t w = static_cast<std::size_t>(0U); (w) <= (cap_size); ++w)
        {
            Value best = prev[w];
            if ((w) >= (wgt))
            {
                const std::size_t idx = (w - wgt);
                const Value candidate = static_cast<Value>(prev[idx] + it.value);
                if ((candidate) > (best))
                {
                    best = candidate;
                }
            }

            dp[w] = best;
        }
    }

    return dp[cap_size];
}

} // namespace knapsack

