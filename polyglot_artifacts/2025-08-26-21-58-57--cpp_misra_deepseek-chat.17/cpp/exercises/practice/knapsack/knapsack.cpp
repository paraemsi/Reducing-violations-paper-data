#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    if ((items.empty()) || (maximumWeight == 0))
    {
        return 0;
    }
    
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items)
    {
        for (std::int32_t w = maximumWeight; w >= item.weight; --w)
        {
            if (dp[w] < (dp[w - item.weight] + item.value))
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    return dp[maximumWeight];
}

std::vector<std::uint32_t> selected_items(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    if ((items.empty()) || (maximumWeight == 0))
    {
        return {};
    }
    
    const std::uint32_t numItems = static_cast<std::uint32_t>(items.size());
    // Create a DP table with number of items + 1 rows and maximumWeight + 1 columns
    std::vector<std::vector<std::int32_t>> dp(numItems + 1, 
                                             std::vector<std::int32_t>(maximumWeight + 1, 0));
    
    // Build the DP table
    for (std::uint32_t i = 1; i <= numItems; ++i)
    {
        const Item& currentItem = items[i - 1];
        for (std::int32_t w = 0; w <= maximumWeight; ++w)
        {
            // If the current item's weight is more than the current capacity, skip it
            if (currentItem.weight > w)
            {
                dp[i][w] = dp[i - 1][w];
            }
            else
            {
                // Otherwise, choose the maximum between including or excluding the item
                if (dp[i - 1][w] > (dp[i - 1][w - currentItem.weight] + currentItem.value))
                {
                    dp[i][w] = dp[i - 1][w];
                }
                else
                {
                    dp[i][w] = dp[i - 1][w - currentItem.weight] + currentItem.value;
                }
            }
        }
    }
    
    // Backtrack to find the selected items
    std::vector<std::uint32_t> selected;
    std::int32_t remainingWeight = maximumWeight;
    for (std::uint32_t i = numItems; i > 0; --i)
    {
        if (dp[i][remainingWeight] != dp[i - 1][remainingWeight])
        {
            selected.push_back(i - 1);
            remainingWeight -= items[i - 1].weight;
            if (remainingWeight < 0)
            {
                break;
            }
        }
    }
    // The items are added in reverse order, so we need to reverse them
    // But actually, the order doesn't matter as long as the indices are correct
    // Let's sort them to be in increasing order of index
    std::sort(selected.begin(), selected.end());
    return selected;
}

} // namespace knapsack

