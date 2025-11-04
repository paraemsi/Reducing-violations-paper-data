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

int maximum_value(int maximum_weight, const std::vector<Item>& items) noexcept;

} // namespace knapsack

#endif // KNAPSACK_H
