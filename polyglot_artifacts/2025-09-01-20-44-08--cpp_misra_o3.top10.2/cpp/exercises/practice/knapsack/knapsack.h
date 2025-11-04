#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

struct Item
{
    std::uint32_t weight;
    std::uint32_t value;
};

/*  Compute the maximal achievable value for the given capacity.
 *  items    : set of available items (each may be taken at most once)
 *  capacity : maximum total weight the knapsack can carry
 */
auto max_value(const std::vector<Item>& items,
               std::uint32_t           capacity) -> std::uint32_t;

/*  Test-suite wrapper – keeps original parameter order used by the tests. */
auto maximum_value(std::uint32_t           capacity,
                   const std::vector<Item>& items) -> std::uint32_t;

} // namespace knapsack

#endif // KNAPSACK_H
