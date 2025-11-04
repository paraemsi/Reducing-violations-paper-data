#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <cstdint>

namespace knapsack
{

using weight_t = std::int32_t;
using value_t = std::int32_t;

struct Item
{
    weight_t weight;
    value_t value;
};

// Returns the maximal value that fits in the knapsack of given capacity.
// items: list of items (each with weight and value)
// capacity: maximum weight the knapsack can carry
// Returns: maximal total value achievable
value_t maximum_value(weight_t capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
