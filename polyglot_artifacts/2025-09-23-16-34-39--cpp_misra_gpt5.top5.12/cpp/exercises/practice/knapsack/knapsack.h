#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

struct Item
{
    std::int32_t weight;
    std::int32_t value;
};

// Compute the maximum value achievable with the given capacity and items.
// Returns the maximum value as an int to maintain compatibility with existing code.
std::int32_t maximum_value(std::int32_t capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
