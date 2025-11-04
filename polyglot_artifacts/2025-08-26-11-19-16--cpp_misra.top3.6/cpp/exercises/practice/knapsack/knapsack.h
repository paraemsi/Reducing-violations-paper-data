#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

using weight_type = std::int32_t;
using value_type = std::int32_t;

struct Item
{
    weight_type weight;
    value_type value;
};

/*
 * Returns the maximum value that can be put in a knapsack of capacity 'max_weight'.
 * items: list of items to choose from
 * max_weight: maximum weight the knapsack can carry
 */
value_type maximum_value(weight_type max_weight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
