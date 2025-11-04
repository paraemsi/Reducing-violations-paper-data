#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>
#include <cstddef>

namespace knapsack
{

struct Item
{
    std::uint32_t weight;
    std::uint32_t value;
};

struct Result
{
    std::uint32_t            max_value;
    std::vector<std::size_t> selected_indices;
};

auto solve(const std::vector<Item>& items, std::uint32_t capacity) -> Result;

auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t;

} // namespace knapsack

#endif // KNAPSACK_H
