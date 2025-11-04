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
 * Compute the maximum total value achievable without exceeding the given capacity.
 *
 * @param capacity  Maximum weight the knapsack can carry.
 * @param items     Vector of available items (weight and value must be positive).
 * @return          Maximum total value obtainable.
 */
int maximum_value(int capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
