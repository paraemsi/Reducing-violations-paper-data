#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <cstdint>

namespace knapsack
{

using Weight = std::int32_t;
using Value = std::int32_t;

struct Item
{
    Weight weight;
    Value value;
};

// Return the maximum total value achievable within the given capacity.
Value maximum_value(Weight capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
