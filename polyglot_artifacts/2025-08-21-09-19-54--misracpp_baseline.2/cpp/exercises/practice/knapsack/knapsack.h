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

/*
 * Returns the maximal value that can be carried in the knapsack with given capacity.
 * items: list of items (each with weight and value)
 * capacity: maximum weight the knapsack can carry
 */
int maximum_value(int capacity, const std::vector<Item>& items);

std::vector<int> optimal_item_indices(int capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
