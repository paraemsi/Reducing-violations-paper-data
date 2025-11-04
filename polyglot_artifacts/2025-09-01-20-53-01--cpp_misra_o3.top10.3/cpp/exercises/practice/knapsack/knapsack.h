#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <cstdint>
#include <vector>

namespace knapsack
{
using WeightType = std::uint32_t;
using ValueType  = std::uint32_t;

struct Item
{
    WeightType weight;
    ValueType  value;
};

/**
 * @brief Compute the maximum achievable value subject to the given weight capacity.
 *
 * @param items    Vector containing the available items.
 * @param capacity Maximum weight capacity of the knapsack.
 * @return Maximum total value that can be carried.
 */
/**
 * Primary overload – preferred when the caller already supplies the exact
 * WeightType.
 */
ValueType maximum_value(WeightType capacity, const std::vector<Item>& items);

/**
 * Convenience overload – preserves MISRA-C++ rule “argument and parameter of a
 * function call should have the same type”.  Unit-tests pass an ‘int’
 * variable; providing this wrapper removes the implicit integral conversion
 * from the test‐site.  Internally we convert explicitly to WeightType.
 */
inline ValueType maximum_value(std::int32_t capacity, const std::vector<Item>& items)
{
    /* Negative capacities are treated as zero. */
    const WeightType safeCap =
        (capacity <= static_cast<std::int32_t>(0)) ?
        static_cast<WeightType>(0U) :
        static_cast<WeightType>(capacity);

    return maximum_value(safeCap, items);
}

} // namespace knapsack

#endif // KNAPSACK_H
