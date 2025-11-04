#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

using weight_type   = std::uint32_t;
using value_type    = std::uint32_t;
using capacity_type = std::uint32_t;

struct Item
{
    weight_type weight;
    value_type  value;
};

value_type maximum_value(capacity_type capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
