#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace knapsack
{

using Weight = std::uint32_t;
using Value = std::uint32_t;

struct Item
{
    Weight weight;
    Value value;
};

// Returns the maximum achievable total value within the given capacity.
Value maximum_value(Weight capacity, const std::vector<Item>& items);

// Returns the indices (into the input vector) of items chosen for an optimal solution.
// Indices are in the order they are discovered during reconstruction; caller may sort if needed.
std::vector<std::size_t> optimal_selection(Weight capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
