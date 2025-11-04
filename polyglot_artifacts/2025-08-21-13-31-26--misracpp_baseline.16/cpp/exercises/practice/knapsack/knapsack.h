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
// Returns the maximum value that can be put in a knapsack of capacity 'maxWeight'.
// 'items' is a vector of Item, each with a weight and value.
// Optionally, if 'selected' is provided, it will be filled with the indices of the items taken.
// Also, for compatibility with tests, provide maximum_value as an alias.
int knapsackMaxValue(const std::vector<Item>& items, int maxWeight, std::vector<int>* selected = nullptr);

// Returns the maximum value that can be put in a knapsack of capacity 'maxWeight'.
// 'items' is a vector of Item, each with a weight and value.
int maximum_value(int maxWeight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
