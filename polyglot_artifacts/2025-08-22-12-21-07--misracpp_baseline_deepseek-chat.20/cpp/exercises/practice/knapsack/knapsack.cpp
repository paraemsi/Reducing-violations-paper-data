#include "knapsack.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace knapsack
{

int maximum_value(int maximumWeight, const vector<Item>& items) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(maximumWeight + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= maximumWeight; w++) {
            // If current item's weight is more than the current capacity, skip it
            if (items[i - 1].weight > w) {
                dp[i][w] = dp[i - 1][w];
            } else {
                // Otherwise, take the maximum between including and not including the item
                dp[i][w] = max(dp[i - 1][w], 
                               dp[i - 1][w - items[i - 1].weight] + items[i - 1].value);
            }
        }
    }
    
    return dp[n][maximumWeight];
}

} // namespace knapsack

