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

/**
 * Compute the maximum total value that can be carried without exceeding the
 * given capacity using a classic 0/1 knapsack dynamic-programming approach.
 *
 * @param capacity Maximum weight the knapsack can carry (non-negative)
 * @param items    The list of available items (each may be chosen at most once)
 * @return         The maximum achievable total value
 */
int maximum_value(int capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
