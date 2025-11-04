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

/**
 * \brief Compute the maximum achievable value that fits within the given
 *        knapsack capacity.
 *
 * \param capacity  Maximum total weight the knapsack can carry.
 * \param items     Collection of available items.
 * \return          The maximum achievable total value.
 */
auto maximum_value(weight_t                 capacity,
                   const std::vector<Item>& items) -> value_t;

} // namespace knapsack

#endif // KNAPSACK_H
