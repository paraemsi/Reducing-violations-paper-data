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
// The 'items' vector contains all available items.
// Optionally, if 'selected' is not nullptr, it will be filled with the indices of the items taken.
int knapsackMaxValue(const std::vector<Item>& items, int maxWeight, std::vector<int>* selected = nullptr);

// Returns the maximum value that can be put in a knapsack of capacity 'maxWeight'.
// The 'items' vector contains all available items.
// This is a simplified interface for test compatibility.
int maximum_value(int maxWeight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
