#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

using uint32 = std::uint32_t;

struct Item
{
    uint32 weight;
    uint32 value;
};

auto maximum_value(uint32 capacity, const std::vector<Item>& items) -> uint32;

} // namespace knapsack

#endif // KNAPSACK_H
