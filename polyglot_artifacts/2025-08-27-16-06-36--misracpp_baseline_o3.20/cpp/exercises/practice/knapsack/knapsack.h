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
 * Calculate the maximum total value that can be carried in a knapsack with the
 * given capacity using the 0-1 knapsack algorithm.
 *
 * @param capacity Maximum weight the knapsack can carry (non-negative).
 * @param items    List of available items (weight > 0, value > 0).
 * @return         Maximum achievable value under the weight constraint.
 */
int maximum_value(int capacity, const std::vector<Item>& items);

} // namespace knapsack

// Legacy global-namespace aliases for backward-compatibility with
// client code that expects these names to live in the global namespace.
using knapsack::maximum_value;
using knapsack::Item;

#endif // KNAPSACK_H
