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
    
    // Find the maximum value in dp up to maximum_weight
    // Since all values are non-negative, the maximum is at dp[maximum_weight]
    // But to be safe, we can find the maximum in the entire array
    return *max_element(dp.begin(), dp.end());
}

} // namespace knapsack

