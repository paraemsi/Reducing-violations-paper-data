#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

using weight_t = std::uint32_t;
using value_t  = std::uint32_t;

struct Item
{
    weight_t weight;
    value_t  value;
};

value_t max_value(const std::vector<Item>& items, weight_t capacity);
value_t maximum_value(weight_t capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
