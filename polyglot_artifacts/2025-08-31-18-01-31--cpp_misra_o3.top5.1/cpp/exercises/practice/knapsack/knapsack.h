#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{


/* Represents an item available to be placed in the knapsack.
 * Both weight and value are strictly positive (as per the problem statement).
 * Declared 'final' to prevent inheritance and accidental slicing.
 */
struct Item final
{
    std::uint32_t weight; /* Weight of the item (> 0) */
    std::uint32_t value;  /* Value of the item  (> 0) */
};

[[nodiscard]] std::uint32_t maximum_value(std::uint32_t capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
