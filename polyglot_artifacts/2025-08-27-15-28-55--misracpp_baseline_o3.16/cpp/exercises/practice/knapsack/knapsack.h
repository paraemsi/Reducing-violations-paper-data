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

int max_value(const std::vector<Item>& items, int max_weight);
int maximum_value(int max_weight, const std::vector<Item>& items);
std::vector<std::size_t> optimal_item_indices(const std::vector<Item>& items, int max_weight);
} // namespace knapsack

#endif // KNAPSACK_H
