#include "knapsack.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace knapsack
{

int maximum_value(int maximumWeight, const vector<Item>& items) {
    // Handle case where maximum weight is 0
    if (maximumWeight == 0) return 0;
    
    // Initialize DP array
    vector<int> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items) {
        // Skip items that are too heavy to ever be included
        if (item.weight > maximumWeight) {
            continue;
        }
        // Process from the end to avoid reusing the same item
        for (int w = maximumWeight; w >= item.weight; w--) {
            if (dp[w - item.weight] + item.value > dp[w]) {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // Find the maximum value which will be at dp[maximumWeight] or less
    // Since all values are non-negative, the maximum will be at the end
    // But to be safe, find the maximum in the entire array
    return *max_element(dp.begin(), dp.end());
}

} // namespace knapsack

