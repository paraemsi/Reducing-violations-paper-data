#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <cstdint>
#include <cstddef>
#include <vector>

namespace knapsack
{

struct Item
{
    std::uint32_t weight; /* weight of the item */
    std::uint32_t value;  /* value of the item */
};

[[nodiscard]] auto max_value(const std::vector<Item>& items, std::uint32_t capacity) -> std::uint32_t;
[[nodiscard]] auto optimal_selection(const std::vector<Item>& items, std::uint32_t capacity) -> std::vector<std::size_t>;
[[nodiscard]] auto maximum_value(std::uint32_t capacity, const std::vector<Item>& items) -> std::uint32_t;

} // namespace knapsack

#endif // KNAPSACK_H
