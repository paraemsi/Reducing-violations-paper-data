#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

/*  Type aliases – comply with MISRA C++: forbid direct use of standard
 *  integer type names outside a typedef / using declaration.
 */
using weight_t = std::uint32_t;
using value_t  = std::uint32_t;

/*  An item that Bob can steal. */
struct Item
{
    weight_t weight;
    value_t  value;
};

/*  Calculate the maximum total value achievable without exceeding
 *  the knapsack capacity.
 *
 *  Param: items    – list of available items
 *  Param: capacity – maximum total weight the knapsack can carry
 *
 *  Return: maximum value that fits within the given capacity
 */
[[nodiscard]] auto max_value(const std::vector<Item>& items,
                             weight_t capacity) -> value_t;
/*  Helper wrapper matching the API used by existing unit-tests
 *  (capacity argument comes first). */
[[nodiscard]] auto maximum_value(weight_t capacity,
                                 const std::vector<Item>& items) -> value_t;

} // namespace knapsack

#endif // KNAPSACK_H
