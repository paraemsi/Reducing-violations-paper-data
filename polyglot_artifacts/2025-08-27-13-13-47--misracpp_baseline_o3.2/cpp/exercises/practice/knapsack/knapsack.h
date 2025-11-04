#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <cstddef> // for std::size_t

namespace knapsack
{

struct Item
{
    int weight; // positive
    int value;  // positive
};

/*
 * Return the maximum achievable total value for the given capacity.
 */
int maximum_value(int capacity, const std::vector<Item>& items);

/*
 * Return the indices (into `items`) that compose an optimal solution.
 * Indices are returned in ascending order.  This helper is optional
 * for callers that only care about the numeric optimum.
 */
std::vector<std::size_t> optimal_item_indices(int capacity,
                                              const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
