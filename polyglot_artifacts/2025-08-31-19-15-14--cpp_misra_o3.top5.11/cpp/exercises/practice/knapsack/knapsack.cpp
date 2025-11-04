#include "knapsack.h"

#include <algorithm>
#include <cstdint>
#include <limits>

namespace knapsack
{

/*-------------------------------------------------------------
 *  max_value : classic 0/1 knapsack (value only)
 *-----------------------------------------------------------*/
auto max_value(const std::vector<Item>& items,
               std::uint32_t             capacity) -> std::uint32_t
{
    /*  One-dimensional DP array – index is current capacity,
     *  value is best total value achievable with that capacity.   */
    std::vector<std::uint32_t> dp(capacity + 1U, 0U);

    for(std::size_t idx = 0U; idx < items.size(); ++idx)
    {
        const std::uint32_t wt = items[idx].weight;
        const std::uint32_t val = items[idx].value;

        /*  Traverse capacities in reverse to avoid re-using items.   */
        for(std::uint32_t w = capacity; w >= wt; --w)
        {
            const std::uint32_t candidate =
                (dp[(w - wt)] + val); /* (dp[(w - wt)] + val) */

            if(candidate > dp[w])
            {
                dp[w] = candidate;
            }
        }
    }

    return dp[capacity];
}

/*-------------------------------------------------------------
 *  maximum_value : wrapper (capacity first) used by tests
 *-----------------------------------------------------------*/
auto maximum_value(std::uint32_t            capacity,
                   const std::vector<Item>& items) -> std::uint32_t
{
    /*  Delegate to internal implementation with swapped parameters.  */
    return max_value(items, capacity);
}

/*-------------------------------------------------------------
 *  solve : returns chosen item indices
 *-----------------------------------------------------------*/
auto solve(const std::vector<Item>& items,
           std::uint32_t            capacity) -> index_list_t
{
    /*  DP arrays for value and backtracking information.  */
    std::vector<std::uint32_t> dp(capacity + 1U, 0U);
    std::vector<std::uint32_t> prev(capacity + 1U, 0U);

    /*  Use a sentinel that will never be produced by a cast
     *  from std::size_t.                                      */
    constexpr std::uint32_t sentinel =
        std::numeric_limits<std::uint32_t>::max();
    std::vector<std::uint32_t> item_idx(capacity + 1U, sentinel);

    for(std::size_t idx = 0U; idx < items.size(); ++idx)
    {
        const std::uint32_t wt = items[idx].weight;
        const std::uint32_t val = items[idx].value;

        for(std::uint32_t w = capacity; w >= wt; --w)
        {
            const std::uint32_t candidate =
                (dp[(w - wt)] + val); /* (dp[(w - wt)] + val) */

            if(candidate > dp[w])
            {
                dp[w] = candidate;
                prev[w] = w - wt;
                item_idx[w] = static_cast<std::uint32_t>(idx);
            }
        }
    }

    /*  Backtrack to reconstruct chosen items.  */
    index_list_t chosen{};
    std::uint32_t w = capacity;

    while((w > 0U) && (item_idx[w] != sentinel))
    {
        chosen.push_back(static_cast<std::size_t>(item_idx[w]));
        w = prev[w];
    }

    std::reverse(chosen.begin(), chosen.end());
    return chosen;
}

} // namespace knapsack

