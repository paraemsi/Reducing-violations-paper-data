#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstddef>
#include <cstdint>
#include <vector>

namespace knapsack
{

struct Item
{
    std::uint32_t weight;
    std::uint32_t value;
};

struct Result
{
    std::uint32_t max_value;
    std::vector<std::size_t> selected_indices;
};

auto solve(std::uint32_t capacity, const std::vector<Item>& items) -> Result;

auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t;

} // namespace knapsack

#endif // KNAPSACK_H
