#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items)
{
    // Handle cases where maximum weight is non-positive
    if (maximum_weight < 0)
    {
        return 0;
    }
    if (items.empty())
    {
        return 0;
    }
    
    // Convert to size_t to avoid signed-unsigned comparisons
    // But since maximum_weight is non-negative, this is safe
    std::vector<std::int32_t> dp(static_cast<std::uint32_t>(maximum_weight) + 1, 0);
    
    for (const auto& item : items)
    {
        // Ensure item weight is non-negative
        // According to the problem, all values are positive, but weights could be?
        // The instructions don't specify, but typically weights are non-negative
        if (item.weight < 0)
        {
            continue; // Skip items with negative weight
        }
        // Process from the end to avoid reusing the same item
        for (std::int32_t w = maximum_weight; w >= item.weight; --w)
        {
            std::int32_t remaining_weight = w - item.weight;
            if (remaining_weight >= 0)
            {
                if (dp[w] < (dp[remaining_weight] + item.value))
                {
                    dp[w] = dp[remaining_weight] + item.value;
                }
            }
        }
    }
    
    // Find the maximum value in the dp array
    // Since all values are positive, the maximum will be at some index
    return *std::max_element(dp.begin(), dp.end());
}

} // namespace knapsack

