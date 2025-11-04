#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstddef>
#include <vector>

namespace knapsack
{

struct Item
{
    int weight;
    int value;
};

/**
 * Compute the maximum attainable value that fits within the given capacity.
 *
 * @param capacity  Maximum weight the knapsack can carry (non-negative).
 * @param items     Collection of available items (weight & value strictly positive).
 * @return          Maximum total value achievable without exceeding capacity.
 */
int maximum_value(int capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
