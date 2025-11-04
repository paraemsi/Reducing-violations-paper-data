#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

value_t maximum_value(weight_t maximum_weight, const std::vector<Item>& items)
{
    if ((maximum_weight <= 0) || items.empty())
    {
        return 0;
    }
    
    // Create a 2D DP table
    // dp[i][w] represents the maximum value that can be obtained
    // with first i items and weight limit w
    std::size_t n = items.size();
    weight_t w_limit = maximum_weight;
    
    // Using vector of vectors for the DP table
    // Adding 1 to dimensions to handle 0-indexed base cases
    std::vector<std::vector<value_t>> dp(n + 1U, 
        std::vector<value_t>(static_cast<std::size_t>(w_limit) + 1U, 0));
    
    // Build the DP table bottom-up
    for (std::size_t i = 1U; i <= n; ++i)
    {
        for (weight_t w = 1; w <= w_limit; ++w)
        {
            // Current item index (0-based)
            std::size_t item_idx = i - 1U;
            
            // Option 1: Don't take the current item
            value_t without_item = dp[i - 1U][static_cast<std::size_t>(w)];
            
            // Option 2: Take the current item (if it fits)
            value_t with_item = 0;
            if (items[item_idx].weight <= w)
            {
                weight_t remaining_weight = w - items[item_idx].weight;
                with_item = items[item_idx].value + 
                    dp[i - 1U][static_cast<std::size_t>(remaining_weight)];
            }
            
            // Take the maximum of both options
            dp[i][static_cast<std::size_t>(w)] = std::max(without_item, with_item);
        }
    }
    
    // The answer is in dp[n][maximum_weight]
    return dp[n][static_cast<std::size_t>(maximum_weight)];
}

} // namespace knapsack
