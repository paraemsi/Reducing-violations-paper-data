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

/*
 * Calculate the maximum attainable value for the given capacity.
 *
 * capacity – maximum total weight Bob can carry.
 * items    – list of available items.
 *
 * Returns the maximum value that fits within the capacity.
 */
auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t;

} // namespace knapsack

#endif // KNAPSACK_H
