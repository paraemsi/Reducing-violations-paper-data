#include "knapsack.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace knapsack
{

int maximum_value(int maximumWeight, const std::vector<Item>& items) {
    if (maximumWeight == 0) return 0;
    std::vector<int> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items) {
        for (int w = maximumWeight; w >= item.weight; w--) {
            if (dp[w - item.weight] + item.value > dp[w]) {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // Find the maximum value in the dp array
    int maxValue = 0;
    for (int w = 0; w <= maximumWeight; w++) {
        if (dp[w] > maxValue) {
            maxValue = dp[w];
        }
    }
    return maxValue;
}

} // namespace knapsack

