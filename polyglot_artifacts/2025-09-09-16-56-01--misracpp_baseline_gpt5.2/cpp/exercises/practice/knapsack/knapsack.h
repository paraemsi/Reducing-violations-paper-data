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
 * Compute the maximum total value achievable with the given capacity,
 * selecting each item at most once (0/1 knapsack).
 */
int maximum_value(int capacity, const std::vector<Item>& items) noexcept;


} // namespace knapsack

#endif // KNAPSACK_H
