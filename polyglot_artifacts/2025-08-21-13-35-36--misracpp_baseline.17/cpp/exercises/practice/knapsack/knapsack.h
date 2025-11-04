#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>

#ifdef __cplusplus
namespace knapsack
{
#endif

struct Item
{
    int weight;
    int value;
};

/**
 * Solves the 0/1 knapsack problem.
 * Returns the maximum value that can be put in a knapsack of capacity 'maxWeight'.
 * The 'taken' vector will be filled with indices of items taken (in any order).
 */
int knapsackMaxValue(const std::vector<Item>& items, int maxWeight, std::vector<int>& taken);

#ifdef __cplusplus
} // namespace knapsack
#endif

// Returns only the maximum value that can be put in a knapsack of capacity 'maxWeight'.
// This is the function expected by the tests.
int maximum_value(int maxWeight, const std::vector<Item>& items);

#endif // KNAPSACK_H
