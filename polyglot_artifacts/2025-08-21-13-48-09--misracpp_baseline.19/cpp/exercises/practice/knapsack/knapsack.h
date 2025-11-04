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

// Solves the 0/1 knapsack problem.
 // Returns the maximum value that can be carried in the knapsack with given capacity.
 // items: vector of Item (each with weight and value)
 // capacity: maximum weight the knapsack can carry
 int maximum_value(int max_weight, const std::vector<Item> &items);

 // Returns a vector of indices of the items to take to achieve the maximum value.
 // The indices refer to the original items vector.
 // If multiple solutions exist, any one is acceptable.
 std::vector<int> knapsack_selected_items(const std::vector<Item> &items, int max_weight);

} // namespace knapsack

#endif // KNAPSACK_H
