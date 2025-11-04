#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <cstddef>

namespace knapsack
{

struct Item
{
    int weight;
    int value;
};

// Solves the 0/1 knapsack problem.
// Returns the maximum value that can be carried in the knapsack.
 // Parameters:
 //   maxWeight: maximum weight the knapsack can carry
 //   items: vector of items (each with weight and value)
int maximum_value(int maxWeight, const std::vector<Item>& items);

 // Returns the indices of the items to take to achieve the maximum value.
 // Parameters:
 //   items: vector of items (each with weight and value)
 //   maxWeight: maximum weight the knapsack can carry
 // Returns:
 //   vector of indices (0-based) of items to take
std::vector<std::size_t> knapsackSelectedItems(const std::vector<Item>& items, int maxWeight);

} // namespace knapsack

#endif // KNAPSACK_H
