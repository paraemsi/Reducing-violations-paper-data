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
 * Solves the 0/1 knapsack problem.
 * @param max_weight maximum weight the knapsack can carry
 * @param items vector of items, each with weight and value
 * @return the maximum total value that fits in the knapsack
 */
int maximum_value(int max_weight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
