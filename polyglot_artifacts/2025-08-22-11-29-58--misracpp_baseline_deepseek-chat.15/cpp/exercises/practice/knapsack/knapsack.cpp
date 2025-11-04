#include "knapsack.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace knapsack
{

int maximum_value(int maximumWeight, const vector<Item>& items) {
    // First, sum up values of all items with weight 0
    int baseValue = 0;
    vector<Item> validItems;
    for (const auto& item : items) {
        if (item.weight == 0) {
            baseValue += item.value;
        } else if (item.weight <= maximumWeight) {
            validItems.push_back(item);
        }
    }
    
    // If maximumWeight is 0, we can only take items with weight 0
    if (maximumWeight == 0) {
        return baseValue;
    }
    
    vector<int> dp(maximumWeight + 1, 0);
    for (const auto& item : validItems) {
        for (int w = maximumWeight; w >= item.weight; w--) {
            dp[w] = max(dp[w], dp[w - item.weight] + item.value);
        }
    }
    
    // Find the maximum value in dp and add baseValue
    int max_value = 0;
    for (int w = 0; w <= maximumWeight; w++) {
        max_value = max(max_value, dp[w]);
    }
    return max_value + baseValue;
}

} // namespace knapsack

