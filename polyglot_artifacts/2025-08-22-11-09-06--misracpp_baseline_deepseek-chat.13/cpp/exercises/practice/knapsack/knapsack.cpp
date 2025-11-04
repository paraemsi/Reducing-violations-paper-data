#include "knapsack.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace knapsack
{

int maximum_value(int maximum_weight, const vector<Item>& items) {
    vector<int> dp(maximum_weight + 1, 0);
    
    for (const auto& item : items) {
        for (int w = maximum_weight; w >= item.weight; w--) {
            dp[w] = max(dp[w], dp[w - item.weight] + item.value);
        }
    }
    
    return dp[maximum_weight];
}

} // namespace knapsack

