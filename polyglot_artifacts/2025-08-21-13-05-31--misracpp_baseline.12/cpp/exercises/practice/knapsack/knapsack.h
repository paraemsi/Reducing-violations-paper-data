#ifndef KNAPSACK_H
#define KNAPSACK_H

namespace knapsack
{

struct Item
{
    int weight;
    int value;
};
int knapsackMaxValue(const Item* items, int itemCount, int maxWeight);

#include <vector>
#include <algorithm>

// New function to match test expectations
// items: std::vector<Item>
template <typename ItemContainer>
int maximum_value(int max_weight, const ItemContainer& items) {
    int n = static_cast<int>(items.size());
    std::vector<int> dp(max_weight + 1, 0);
    for (int i = 0; i < n; ++i) {
        int item_weight = items[i].weight;
        int item_value = items[i].value;
        for (int w = max_weight; w >= item_weight; --w) {
            dp[w] = std::max(dp[w], dp[w - item_weight] + item_value);
        }
    }
    return dp[max_weight];
}

} // namespace knapsack

#endif // KNAPSACK_H
