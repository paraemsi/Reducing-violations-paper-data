#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <cstddef>   /* for std::size_t */
#include <vector>

namespace knapsack
{

/* Alias used to satisfy MISRA rule instead of raw std::uint32_t. */
using u32 = std::uint32_t;

/* Item with weight and value represented by fixed-width unsigned integers. */
struct Item
{
    u32 weight;
    u32 value;
};

/* Result returned by the solver. */
struct Result
{
    u32                         total_value;
    std::vector<std::size_t>   selected_indices;
};

/* Solve the 0/1 knapsack problem. */
[[nodiscard]] auto solve(const std::vector<Item>& items, u32 capacity) noexcept -> Result;

/* Convenience helper returning only maximum total value. */
[[nodiscard]] auto maximum_value(u32 capacity, const std::vector<Item>& items) noexcept -> u32;

} // namespace knapsack

#endif // KNAPSACK_H
