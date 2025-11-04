#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <cstddef>

namespace knapsack
{

struct Item
{
    int weight;
    int value;
};

// Compute and return the maximal total value attainable without
// exceeding max_weight using the 0/1-knapsack constraints.
int max_value(const std::vector<Item>& items, int max_weight);
int maximum_value(int max_weight, const std::vector<Item>& items);

// Return the indices of the items (with respect to the input order) that
// achieve the maximal value without exceeding max_weight.
// If multiple optimal solutions exist, any one is returned.
std::vector<std::size_t> select_items(const std::vector<Item>& items,
                                      int max_weight);

} // namespace knapsack

#endif // KNAPSACK_H
