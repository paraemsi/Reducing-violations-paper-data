#include "knapsack.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdint>

namespace knapsack
{

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items)
{
    if (items.empty() || maximumWeight == 0)
    {
        return 0;
    }
    
    // Use a 1D DP array to save space
    std::vector<std::int32_t> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items)
    {
        // Process weights in reverse to avoid reusing the same item
        for (std::int32_t w = maximumWeight; w >= item.weight; w--)
        {
            if (dp[w - item.weight] + item.value > dp[w])
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    return dp[maximumWeight];
}

std::vector<std::size_t> solveKnapsack(const std::vector<Item>& items, std::int32_t maximumWeight)
{
    if (items.empty()) 
    {
        return {};
    }
    
    // Handle case where maximum weight is 0
    if (maximumWeight == 0) 
    {
        return {};
    }
    
    // Create a DP table where dp[i][w] represents the maximum value using first i items with weight w
    std::vector<std::vector<std::int32_t>> dp(items.size() + 1, std::vector<std::int32_t>(maximumWeight + 1, 0));
    // Create a choice table to track if item i is included at weight w
    std::vector<std::vector<bool>> choice(items.size() + 1, std::vector<bool>(maximumWeight + 1, false));
    
    for (std::size_t i = 0; i < items.size(); i++) 
    {
        for (std::int32_t w = 1; w <= maximumWeight; w++) 
        {
            // Start by not taking the item
            dp[i + 1][w] = dp[i][w];
            if (items[i].weight <= w) 
            {
                std::int32_t valueWithItem = dp[i][w - items[i].weight] + items[i].value;
                if (valueWithItem > dp[i + 1][w]) 
                {
                    dp[i + 1][w] = valueWithItem;
                    choice[i][w] = true;
                }
            }
        }
    }
    
    // Backtrack to find the selected items
    std::vector<std::size_t> result;
    std::int32_t remainingWeight = maximumWeight;
    for (std::int32_t i = static_cast<std::int32_t>(items.size()) - 1; i >= 0; i--) 
    {
        if (choice[i][remainingWeight]) 
        {
            result.push_back(static_cast<std::size_t>(i));
            remainingWeight -= items[i].weight;
        }
    }
    
    // Sort the indices in increasing order
    std::sort(result.begin(), result.end());
    return result;
}

} // namespace knapsack

