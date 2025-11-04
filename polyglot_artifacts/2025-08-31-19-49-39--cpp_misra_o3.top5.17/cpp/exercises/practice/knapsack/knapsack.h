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

/**
 * @brief Compute maximum achievable value without exceeding knapsack capacity.
 *
 * Implements the 0/1 knapsack dynamic-programming algorithm.
 *
 * @param capacity  Maximum weight that the knapsack can carry.
 * @param items     List of available items.
 * @return Maximum total value obtainable with the given capacity.
 */
auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t;

} // namespace knapsack

#endif // KNAPSACK_H
