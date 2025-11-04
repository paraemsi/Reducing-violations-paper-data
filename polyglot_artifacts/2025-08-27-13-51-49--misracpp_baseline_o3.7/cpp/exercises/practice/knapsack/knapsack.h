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

[[nodiscard]] int maximum_value(int max_weight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
