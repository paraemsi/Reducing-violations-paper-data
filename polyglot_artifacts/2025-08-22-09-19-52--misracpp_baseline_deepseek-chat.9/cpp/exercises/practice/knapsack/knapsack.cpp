#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int maximumWeight, const std::vector<Item>& items) {
    if (items.empty() || maximumWeight == 0) {
        return 0;
    }
    
    // Create a DP array where dp[i] = maximum value with weight i
    std::vector<int> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items) {
        // To avoid reusing the same item, we process from the end
        for (int w = maximumWeight; w >= item.weight; w--) {
            if (dp[w - item.weight] + item.value > dp[w]) {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // Find the maximum value in the dp array
    return *std::max_element(dp.begin(), dp.end());
}

} // namespace knapsack

