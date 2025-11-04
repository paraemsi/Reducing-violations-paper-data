#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <cstdint>

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
 * Returns the maximal value that fits in the knapsack of given capacity.
 * items: list of items to choose from
 * capacity: maximum total weight allowed
 * Returns: maximal total value achievable
 */
value_type maximum_value(weight_type capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
