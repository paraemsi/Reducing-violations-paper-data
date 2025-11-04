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

/*
 * Compute the maximum attainable value that fits within the knapsack
 * capacity using a 0-1 knapsack dynamic-programming algorithm.
 */
[[nodiscard]] value_t maximum_value(weight_t capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
