#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int maximumWeight, const std::vector<Item>& items) {
    if (items.empty()) return 0;
    
    // dp[i] will store the maximum value achievable with weight i
    std::vector<int> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items) {
        // To avoid reusing the same item, we process from the end
        for (int w = maximumWeight; w >= item.weight; w--) {
            if (dp[w - item.weight] + item.value > dp[w]) {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // Find the maximum value in dp array
    int maxValue = 0;
    for (int w = 0; w <= maximumWeight; w++) {
        if (dp[w] > maxValue) {
            maxValue = dp[w];
        }
    }
    return maxValue;
}

} // namespace knapsack

