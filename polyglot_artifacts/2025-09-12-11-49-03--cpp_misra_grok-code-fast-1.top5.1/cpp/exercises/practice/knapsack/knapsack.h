#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

using Weight = std::int32_t;
using Value = std::int32_t;
using Capacity = std::int32_t;

struct Item
{
    Weight weight;
    Value value;
};

Value maximum_value(Capacity maxWeight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
