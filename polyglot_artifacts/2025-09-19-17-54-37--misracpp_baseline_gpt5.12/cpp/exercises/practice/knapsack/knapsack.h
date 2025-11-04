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

// Returns the maximum achievable total value for the given capacity.
int maximum_value(int capacity, const std::vector<Item>& items);

// Overload for convenience (items first).
int maximum_value(const std::vector<Item>& items, int capacity);

// Returns the list of items that achieves a maximum value
// for the given capacity. If multiple optimal solutions exist,
// one of them is returned.
std::vector<Item> optimal_items(int capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
