#include "knapsack.h"

#include <algorithm>
#include <cstddef>
#include <limits>
#include <vector>

namespace knapsack
{

auto solve_knapsack(std::uint64_t capacity, const std::vector<Item>& items) -> Solution
{
    Solution result{};

    if ((capacity == static_cast<std::uint64_t>(0U)) || (items.empty()))
    {
        return result;
    }

    const std::size_t n = items.size();

    // Convert capacity to std::size_t safely for indexing
    std::size_t W = static_cast<std::size_t>(0U);
    {
        if (capacity > static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max()))
        {
            // Capacity too large to allocate reasonable DP table
            return result;
        }
        W = static_cast<std::size_t>(capacity);
    }

    // dp[i][w] = maximum value using first i items with capacity w
    std::vector<std::vector<std::uint64_t>> dp((n + static_cast<std::size_t>(1U)),
                                               std::vector<std::uint64_t>((W + static_cast<std::size_t>(1U)), static_cast<std::uint64_t>(0U)));
    // take[i-1][w] indicates whether item (i-1) is taken at capacity w in optimal solution for first i items
    std::vector<std::vector<bool>> take(n, std::vector<bool>((W + static_cast<std::size_t>(1U)), false));

    for (std::size_t i = static_cast<std::size_t>(1U); i <= n; ++i)
    {
        const Item& it = items[i - static_cast<std::size_t>(1U)];
        const std::uint64_t val64 = it.value;
        const std::uint64_t wt64 = it.weight;

        // Derive weight in size_t if representable
        std::size_t wgt = static_cast<std::size_t>(0U);
        bool weight_valid = false;
        {
            const std::uint64_t w_u64 = wt64;
            if (w_u64 <= static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max()))
            {
                wgt = static_cast<std::size_t>(w_u64);
                weight_valid = true;
            }
        }

        const std::size_t i_prev = i - static_cast<std::size_t>(1U);
        for (std::size_t w = static_cast<std::size_t>(0U); w <= W; ++w)
        {
            dp[i][w] = dp[i_prev][w];

            if (weight_valid)
            {
                if (w >= wgt)
                {
                    const std::size_t w_rem = w - wgt;
                    const std::uint64_t candidate = (dp[i_prev][w_rem] + val64);
                    if (candidate > dp[i][w])
                    {
                        dp[i][w] = candidate;
                        take[i_prev][w] = true;
                    }
                }
            }
        }
    }

    // Reconstruct chosen items
    std::size_t w = W;
    for (std::size_t i = n; i > static_cast<std::size_t>(0U); --i)
    {
        const std::size_t idx = i - static_cast<std::size_t>(1U);
        const Item& it = items[idx];
        const std::uint64_t wt64 = it.weight;

        if (take[idx][w])
        {
            std::size_t wgt = static_cast<std::size_t>(0U);
            if (wt64 <= static_cast<std::uint64_t>(std::numeric_limits<std::size_t>::max()))
            {
                wgt = static_cast<std::size_t>(wt64);
                if (w >= wgt)
                {
                    result.items.push_back(idx);
                    w = (w - wgt);
                }
            }
        }
    }

    std::reverse(result.items.begin(), result.items.end());
    result.maximum_value = dp[n][W];

    return result;
}

auto maximum_value(std::uint64_t capacity, const std::vector<Item>& items) -> std::uint64_t
{
    const Solution sol = solve_knapsack(capacity, items);
    return sol.maximum_value;
}

} // namespace knapsack

