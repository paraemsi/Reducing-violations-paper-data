#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <cstdint>

namespace knapsack
{

struct Item
{
    std::int32_t weight;
    std::int32_t value;
};

auto maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items) -> std::int32_t;

} // namespace knapsack

#endif // KNAPSACK_H
