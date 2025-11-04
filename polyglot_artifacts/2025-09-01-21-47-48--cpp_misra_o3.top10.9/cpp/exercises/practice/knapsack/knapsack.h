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

/*  Compute the maximum achievable value for the given capacity.
 *  @param capacity  The maximum total weight the knapsack can hold.
 *  @param items     Collection of available items.
 *  @return          The maximum attainable value.
 */
[[nodiscard]] value_t maximum_value(const weight_t capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
