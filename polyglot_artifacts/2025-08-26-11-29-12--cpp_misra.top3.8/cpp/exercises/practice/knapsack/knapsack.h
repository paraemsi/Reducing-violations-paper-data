#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

using weight_t = std::int32_t;
using value_t = std::int32_t;

struct Item
{
    weight_t weight;
    value_t value;
};

// Returns the maximum value that can be carried in the knapsack with the given capacity.
// items: list of items (each with weight and value)
// capacity: maximum weight the knapsack can carry
value_t maximum_value(weight_t capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
