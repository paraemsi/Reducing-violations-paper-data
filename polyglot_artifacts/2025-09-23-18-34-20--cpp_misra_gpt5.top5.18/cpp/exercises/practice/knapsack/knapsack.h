#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace knapsack
{

struct Item
{
    std::uint64_t weight { static_cast<std::uint64_t>(0U) };
    std::uint64_t value { static_cast<std::uint64_t>(0U) };
};

using Index = std::size_t;

struct Solution
{
    std::uint64_t maximum_value { static_cast<std::uint64_t>(0U) };
    std::vector<Index> items;
};

auto maximum_value(std::uint64_t capacity, const std::vector<Item>& items) -> std::uint64_t;
auto solve_knapsack(std::uint64_t capacity, const std::vector<Item>& items) -> Solution;

} // namespace knapsack

#endif // KNAPSACK_H
