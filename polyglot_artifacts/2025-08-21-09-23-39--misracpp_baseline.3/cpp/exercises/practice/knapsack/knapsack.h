#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>

namespace knapsack
{

struct Item
{
    int weight;
    int value;
};

// Returns the maximum value that can be put in a knapsack of capacity 'max_weight'.
// 'items' is a vector of Item, each with a weight and value.
// Returns the maximum total value that can be achieved.
int maximum_value(int max_weight, const std::vector<Item>& items);

// Returns a vector of indices of the items to take to achieve the maximum value.
// The indices refer to the positions in the input 'items' vector.
// If multiple solutions exist, any one is acceptable.
std::vector<int> optimal_item_indices(int max_weight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
