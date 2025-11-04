#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

using uint32 = std::uint32_t;
using int64  = std::int64_t;

struct Item
{
    uint32 weight;
    uint32 value;
};

[[nodiscard]] uint32 max_value(const std::vector<Item>& items, uint32 capacity);
[[nodiscard]] uint32 maximum_value(uint32 capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
