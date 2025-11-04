#include "knapsack.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace knapsack
{

int maximum_value(int maximum_weight, const vector<Item>& items) {
    // First, sum up values of all items with weight 0
    int zero_weight_value = 0;
    vector<Item> valid_items;
    for (const auto& item : items) {
        if (item.weight == 0) {
            zero_weight_value += item.value;
        } else if (item.weight <= maximum_weight) {
            valid_items.push_back(item);
        }
    }
    
    // Now process items with weight > 0
    vector<int> dp(maximum_weight + 1, 0);
    for (const auto& item : valid_items) {
        for (int w = maximum_weight; w >= item.weight; w--) {
            if (dp[w - item.weight] + item.value > dp[w]) {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    return dp[maximum_weight] + zero_weight_value;
}

} // namespace knapsack

