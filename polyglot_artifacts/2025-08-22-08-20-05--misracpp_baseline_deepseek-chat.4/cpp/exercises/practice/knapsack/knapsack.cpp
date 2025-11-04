#include "knapsack.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace knapsack
{

int maximum_value(int maximumWeight, const vector<Item>& items) {
    if (maximumWeight == 0) return 0;
    
    vector<int> dp(maximumWeight + 1, 0);
    
    for (const auto& item : items) {
        for (int w = maximumWeight; w >= item.weight; w--) {
            dp[w] = max(dp[w], dp[w - item.weight] + item.value);
        }
    }
    
    return dp[maximumWeight];
}

} // namespace knapsack

