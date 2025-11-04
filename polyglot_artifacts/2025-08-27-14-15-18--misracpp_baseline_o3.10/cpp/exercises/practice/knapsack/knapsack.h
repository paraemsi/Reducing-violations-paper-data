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
 * Compute the maximum achievable value for the 0/1 knapsack problem.
 *
 * @param capacity  Maximum weight capacity of the knapsack (non-negative).
 * @param items     Collection of available items.
 * @return          Maximum total value that fits within the capacity.
 */
int maximum_value(int capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
