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
 * @brief Compute the maximum total value that fits into a knapsack
 *        with the specified capacity using the 0/1 knapsack algorithm.
 *
 * @param capacity Maximum weight the knapsack can carry
 * @param items    List of available items (weight-value pairs)
 * @return Maximum attainable value without exceeding capacity
 */
std::uint32_t maximum_value(std::uint32_t capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
