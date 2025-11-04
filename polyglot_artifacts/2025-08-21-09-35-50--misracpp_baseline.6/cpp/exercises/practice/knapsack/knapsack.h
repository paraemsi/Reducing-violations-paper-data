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

/*
Solves the 0/1 knapsack problem.
Returns the maximum value that can be carried in the knapsack with given capacity.
Optionally, fills 'selected' with the indices of the items taken (if not nullptr).
*/

/**
 * Returns the maximum value that can be carried in the knapsack with given capacity.
 */
int maximum_value(int max_weight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
