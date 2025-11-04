#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

struct Item
{
    std::uint32_t weight{0U}; /* Weight of the item */
    std::uint32_t value{0U};  /* Value of the item */
};

/* Determine the maximum achievable value without exceeding capacity */
[[nodiscard]] auto max_value(const std::vector<Item>& items, std::uint32_t capacity) -> std::uint32_t;

/* Wrapper with the parameter order expected by the test-suite */
[[nodiscard]] auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t;

} // namespace knapsack

#endif // KNAPSACK_H
