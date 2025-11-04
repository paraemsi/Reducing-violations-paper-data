#include "knapsack.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace knapsack
{

int maximum_value(int maximum_weight, const vector<Item>& items) {
    if (maximum_weight < 0) return 0;
    if (items.empty()) return 0;
    
    vector<int> dp(maximum_weight + 1, 0);
    
    for (const auto& item : items) {
        // To avoid reusing the same item, we process from the end
        for (int w = maximum_weight; w >= item.weight; w--) {
            dp[w] = max(dp[w], dp[w - item.weight] + item.value);
        }
    }
    
    return dp[maximum_weight];
}

} // namespace knapsack

