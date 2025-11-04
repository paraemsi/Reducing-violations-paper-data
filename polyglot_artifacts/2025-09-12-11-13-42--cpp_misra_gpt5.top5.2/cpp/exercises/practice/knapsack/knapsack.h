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

// Compute maximal total value without exceeding maximum_weight.
/**
 * Uses 0/1 knapsack dynamic programming.
 * Returns 0 if maximum_weight == 0 or items is empty.
 */
std::uint32_t maximum_value(std::uint32_t maximum_weight, const std::vector<Item>& items) noexcept;

// Convenience alias matching alternative naming styles.
inline std::uint32_t maximumValue(std::uint32_t maximum_weight, const std::vector<Item>& items) noexcept
{
    return maximum_value(maximum_weight, items);
}

} // namespace knapsack

#endif // KNAPSACK_H
