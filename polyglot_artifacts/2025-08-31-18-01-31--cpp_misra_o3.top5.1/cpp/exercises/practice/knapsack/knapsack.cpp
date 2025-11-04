#include "knapsack.h"
#include <algorithm>

namespace knapsack
{

std::uint32_t maximum_value(std::uint32_t capacity, const std::vector<Item>& items)
{
    /* Dynamic programming table where dp[w] stores the maximum value reachable
       with exact weight w. */
    std::vector<std::uint32_t> dp((capacity + static_cast<std::uint32_t>(1U)),
                                  static_cast<std::uint32_t>(0U));

    for(const Item& item : items)
    {
        /* Iterate weights in descending order to ensure each item is used at most once. */
        for(std::uint32_t w = capacity; w >= item.weight; --w)
        {
            dp[w] = std::max(dp[w],
                             dp[(w - item.weight)] + item.value);
        }
    }

    /* The optimal total value might be achieved with a load that is
     * strictly less than the full capacity, therefore we take the
     * maximum value across all reachable weights ≤ capacity. */
    return *std::max_element(dp.begin(), dp.end());
}

} // namespace knapsack

