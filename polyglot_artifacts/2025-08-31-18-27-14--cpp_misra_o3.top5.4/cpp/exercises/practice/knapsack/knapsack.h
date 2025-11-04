#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

/*  MISRA-compliant representation of an item that can be placed in the knapsack.
 *  Both weight and value are non-negative and fit in 32-bit unsigned integers.
 */
struct Item
{
    std::uint32_t weight;
    std::uint32_t value;
};

/*  Compute the maximum total value that can be carried in a knapsack
 *  with the specified capacity.
 *
 *  param capacity Maximum weight that the knapsack can hold
 *  param items    List of available items (each may be taken at most once)
 *  return         Maximum total value achievable without exceeding capacity
 */
auto maximum_value(std::uint32_t             capacity,
                   const std::vector<Item>& items) -> std::uint32_t;

} // namespace knapsack

#endif // KNAPSACK_H
