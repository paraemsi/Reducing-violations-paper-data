#include "knapsack.h"

#include <vector>
#include <cstdint>
#include <algorithm>   // for std::reverse

namespace knapsack
{

weight_value_t solveKnapsack(const std::vector<Item>& items, weight_value_t maxWeight)
{
    /* Two-dimensional dynamic programming – handles zero-weight items safely */
    const std::size_t n{items.size()};
    std::vector<std::vector<weight_value_t>> dp(
        n + 1U,
        std::vector<weight_value_t>(static_cast<std::size_t>(maxWeight) + 1U, static_cast<weight_value_t>(0)));

    for(std::size_t i{1U}; i <= n; ++i)
    {
        const weight_value_t w{items[i - 1U].weight};
        const weight_value_t v{items[i - 1U].value};

        for(weight_value_t weight{0}; weight <= maxWeight; ++weight)
        {
            const std::size_t idx{static_cast<std::size_t>(weight)};
            if(weight < w)
            {
                dp[i][idx] = dp[i - 1U][idx];
            }
            else
            {
                const weight_value_t withoutItem{dp[i - 1U][idx]};
                const weight_value_t withItem{
                    static_cast<weight_value_t>(v + dp[i - 1U][static_cast<std::size_t>(weight - w)])};
                dp[i][idx] = (withItem > withoutItem) ? withItem : withoutItem;
            }
        }
    }

    return dp[n][static_cast<std::size_t>(maxWeight)];
}

weight_value_t maximum_value(weight_value_t maxWeight, const std::vector<Item>& items)
{
    /* Wrapper to maintain legacy interface required by unit tests */
    return solveKnapsack(items, maxWeight);
}

std::vector<std::size_t> selectItems(const std::vector<Item>& items, weight_value_t maxWeight)
{
    const std::size_t n{items.size()};
    std::vector<std::vector<weight_value_t>> dp(n + 1U, std::vector<weight_value_t>(static_cast<std::size_t>(maxWeight) + 1U, static_cast<weight_value_t>(0)));

    for(std::size_t i{1U}; i <= n; ++i)
    {
        const weight_value_t w{items[i - 1U].weight};
        const weight_value_t v{items[i - 1U].value};

        for(weight_value_t weight{0}; weight <= maxWeight; ++weight)
        {
            const std::size_t idx{static_cast<std::size_t>(weight)};
            if(weight < w)
            {
                dp[i][idx] = dp[i - 1U][idx];
            }
            else
            {
                const weight_value_t withoutItem{dp[i - 1U][idx]};
                const weight_value_t withItem{static_cast<weight_value_t>(v + dp[i - 1U][static_cast<std::size_t>(weight - w)])};
                dp[i][idx] = (withItem > withoutItem) ? withItem : withoutItem;
            }
        }
    }

    std::vector<std::size_t> selected{};
    weight_value_t weight{maxWeight};
    for(std::size_t i{n}; i > 0U; --i)
    {
        const std::size_t idx{static_cast<std::size_t>(weight)};
        if(dp[i][idx] != dp[i - 1U][idx])
        {
            selected.push_back(i - 1U);
            const weight_value_t w{items[i - 1U].weight};
            weight -= w;
        }
    }

    /* Ensure indices are returned in ascending order for determinism */
    std::reverse(selected.begin(), selected.end());

    return selected;
}

} // namespace knapsack

