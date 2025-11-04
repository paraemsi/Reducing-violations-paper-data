#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

using Weight = std::uint32_t;
using Value = std::uint32_t;

struct Item
{
    Weight weight;
    Value value;
};

Value maximum_value(Weight capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
