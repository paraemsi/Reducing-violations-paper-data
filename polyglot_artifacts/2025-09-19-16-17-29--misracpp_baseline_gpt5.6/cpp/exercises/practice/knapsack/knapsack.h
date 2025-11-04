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

// Compute the maximum total value obtainable without exceeding maximum_weight.
// 0/1 knapsack: each item can be taken at most once.
int maximum_value(int maximum_weight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
