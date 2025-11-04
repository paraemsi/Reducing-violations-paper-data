#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

using weight_type = std::uint32_t;
using value_type  = std::uint32_t;

struct Item
{
    weight_type weight;
    value_type  value;

    /*------------------------------------------------------------------------*/
    /* Constructors                                                           */
    /*------------------------------------------------------------------------*/
    /* Default-construct an “empty” item. */
    constexpr Item() noexcept
        : weight(static_cast<weight_type>(0U)),
          value(static_cast<value_type>(0U))
    {
    }

    /* Construct from explicit weight/value pairs.  The caller ensures the
       arguments are within the valid range of the target unsigned types. */
    constexpr Item(weight_type w, value_type v) noexcept
        : weight(w), value(v)
    {
    }
};

/**
 * @brief Compute the maximum attainable value within the provided capacity.
 *
 * @param items     Collection of available items.
 * @param capacity  Maximum total weight that the knapsack can carry.
 * @return          The greatest value achievable without exceeding @p capacity.
 */
value_type max_value(const std::vector<Item>& items,
                     weight_type               capacity);

/**
 * @brief Convenience wrapper matching legacy parameter order expected by tests.
 *
 * @param capacity  Maximum total weight that the knapsack can carry.
 * @param items     Collection of available items.
 * @return          The greatest value achievable without exceeding @p capacity.
 */
value_type maximum_value(weight_type               capacity,
                         const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
