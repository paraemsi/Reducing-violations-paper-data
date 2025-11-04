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
/**
 * Returns the maximum value that can be carried in the knapsack with given capacity.
 * @param items vector of Item (each with weight and value)
 * @param capacity maximum weight the knapsack can carry
 */
int knapsack_max_value(const std::vector<Item>& items, int capacity);

// For compatibility with tests expecting knapsack::maximum_value(max_weight, items)
inline int maximum_value(int max_weight, const std::vector<Item>& items) {
    return knapsack_max_value(items, max_weight);
}

/**
 * Returns a vector of indices of the items to take to achieve the maximum value.
 * The indices refer to the original items vector.
 * @param items vector of Item (each with weight and value)
 * @param capacity maximum weight the knapsack can carry
 */
std::vector<int> knapsack_selected_items(const std::vector<Item>& items, int capacity);

} // namespace knapsack

#endif // KNAPSACK_H
