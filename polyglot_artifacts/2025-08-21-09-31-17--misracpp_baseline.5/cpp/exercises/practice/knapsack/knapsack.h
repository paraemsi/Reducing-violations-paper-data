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

/**
 * Solves the 0/1 knapsack problem.
 * Returns the maximum value that can be put in a knapsack of capacity 'maxWeight'.
 * The 'items' vector contains all available items.
 * This is an alias for compatibility with tests.
 */
int knapsackMaxValue(const std::vector<Item>& items, int maxWeight);

int maximum_value(int max_weight, const std::vector<Item>& items);

std::vector<std::size_t> knapsackSelectedItems(const std::vector<Item>& items, int maxWeight);

} // namespace knapsack

#endif // KNAPSACK_H
