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

// Returns the maximal value that fits in the knapsack with given capacity.
// items: list of items (each with weight and value)
// capacity: maximum weight the knapsack can carry
int maximum_value(const std::vector<Item>& items, int capacity);

} // namespace knapsack

#endif // KNAPSACK_H
