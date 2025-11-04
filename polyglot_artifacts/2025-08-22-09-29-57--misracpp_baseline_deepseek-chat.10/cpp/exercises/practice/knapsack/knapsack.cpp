#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int maximumWeight, const std::vector<Item>& items) {
    std::vector<int> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items) {
        // Process weights in reverse to avoid reusing the same item
        for (int w = maximumWeight; w >= item.weight; w--) {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }
    
    return dp[maximumWeight];
}

} // namespace knapsack

