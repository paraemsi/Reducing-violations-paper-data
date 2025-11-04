#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace knapsack
{

using weight_t = std::uint64_t;
using value_t = std::uint64_t;

struct Item
{
    weight_t weight;
    value_t value;
};

 // Returns the maximum achievable value for the given capacity and items.
[[nodiscard]] value_t maximum_value(weight_t capacity, const std::vector<Item>& items) noexcept;

 // Returns the indices (0-based) of items chosen to achieve an optimal value.
 // If multiple optimal solutions exist, any one may be returned.
[[nodiscard]] std::vector<std::size_t> choose_items(weight_t capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
