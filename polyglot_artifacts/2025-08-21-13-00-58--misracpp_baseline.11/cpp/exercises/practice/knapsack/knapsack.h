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
 * @param items: vector of items, each with weight and value
 * @param max_weight: maximum weight the knapsack can carry
 * @return the maximum total value that fits in the knapsack
 */
int maximum_value(const std::vector<Item>& items, int max_weight);

} // namespace knapsack

#endif // KNAPSACK_H
