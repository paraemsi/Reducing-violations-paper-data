#include "knapsack.h"

#include <algorithm>   // for std::reverse
#include <cstddef>     // for std::size_t
#include <vector>

namespace knapsack
{

auto solve(std::uint32_t capacity, const std::vector<Item>& items) -> Result
{
    const std::size_t itemCount = items.size();
    const std::size_t capacitySizeT = static_cast<std::size_t>(capacity);
    std::vector<std::vector<std::uint32_t>> dp(
        itemCount + static_cast<std::size_t>(1),
        std::vector<std::uint32_t>(capacitySizeT + static_cast<std::size_t>(1), 0U));

    for (std::size_t i = 1U; i <= itemCount; ++i)
    {
        const std::uint32_t itemWeight = items[i - 1U].weight;
        const std::uint32_t itemValue = items[i - 1U].value;

        for (std::size_t w = 0U; w <= capacitySizeT; ++w)
        {
            if (static_cast<std::size_t>(itemWeight) <= w)
            {
                const std::uint32_t valueWithItem =
                    itemValue + dp[i - 1U][w - static_cast<std::size_t>(itemWeight)];
                const std::uint32_t valueWithoutItem = dp[i - 1U][w];
                dp[i][w] = (valueWithItem > valueWithoutItem)
                               ? valueWithItem
                               : valueWithoutItem;
            }
            else
            {
                dp[i][w] = dp[i - 1U][w];
            }
        }
    }

    Result result{};
    result.max_value = dp[itemCount][capacitySizeT];

    std::size_t w = capacitySizeT;
    for (std::size_t i = itemCount; i > 0U; --i)
    {
        if (dp[i][w] != dp[i - 1U][w])
        {
            result.selected_indices.push_back(i - 1U);
            w = w - static_cast<std::size_t>(items[i - 1U].weight);
        }
    }

    std::reverse(result.selected_indices.begin(),
                 result.selected_indices.end());
    return result;
}

auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t
{
    return solve(capacity, items).max_value;
}

} // namespace knapsack

