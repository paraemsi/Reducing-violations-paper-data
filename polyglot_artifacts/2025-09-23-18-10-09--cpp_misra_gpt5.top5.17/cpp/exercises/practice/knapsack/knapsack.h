#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace knapsack
{

struct Item
{
    std::size_t weight;
    std::size_t value;
};

auto maximum_value(std::size_t max_weight, const std::vector<Item>& items) -> std::size_t;

} // namespace knapsack

#endif // KNAPSACK_H
