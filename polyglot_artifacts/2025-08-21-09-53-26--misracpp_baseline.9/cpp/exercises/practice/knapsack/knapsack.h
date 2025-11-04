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

// Returns the maximal value that can be carried in the knapsack with given capacity.
// items: list of items (each with weight and value)
// capacity: maximum weight the knapsack can carry
int maximum_value(const std::vector<Item> &items, int capacity);

// Returns the indices of the items to take to achieve the maximal value.
// The indices refer to the positions in the input vector.
// If multiple solutions exist, any one is acceptable.
std::vector<int> optimal_item_indices(const std::vector<Item> &items, int capacity);

} // namespace knapsack

#endif // KNAPSACK_H
