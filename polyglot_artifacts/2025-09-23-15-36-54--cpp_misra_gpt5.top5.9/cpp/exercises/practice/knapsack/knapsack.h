#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

struct Item
{
    std::uint32_t weight;
    std::uint32_t value;
};

std::uint32_t maximum_value(std::uint32_t max_weight, const std::vector<Item> &items);

} // namespace knapsack

#endif // KNAPSACK_H
