#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

struct Item
{
    /* Weight of the item in arbitrary units (must be greater than 0). */
    std::uint32_t weight;
    /* Monetary value associated with the item. */
    std::uint32_t value;
};

/*
 * Determine the maximum total value that can be carried without
 * exceeding the provided capacity.
 *
 * capacity : maximum total weight the knapsack can contain
 * items    : list of candidate items
 *
 * returns the highest achievable value
 */
[[nodiscard]] auto maximum_value(std::uint32_t capacity,
                                 const std::vector<Item>& items) -> std::uint32_t;

/* --------------------------------------------------------------------
 * Convenience overload
 * --------------------------------------------------------------------
 * Some client code (e.g. the unit-tests) passes a signed integer for the
 * capacity argument.  Accepting such calls directly avoids the implicit
 * signed-to-unsigned conversion that would otherwise violate our MISRA
 * rules.  The overload verifies that the supplied capacity is
 * non-negative before forwarding the request to the primary unsigned
 * implementation.
 */
[[nodiscard]] inline auto maximum_value(int capacity,
                                        const std::vector<Item>& items) -> std::uint32_t
{
    if (capacity <= 0)
    {
        return 0U;
    }
    return maximum_value(static_cast<std::uint32_t>(capacity), items);
}

} // namespace knapsack

#endif // KNAPSACK_H
