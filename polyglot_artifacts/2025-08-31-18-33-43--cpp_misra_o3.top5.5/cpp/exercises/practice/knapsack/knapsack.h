#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <cstddef>
#include <vector>

namespace knapsack
{

struct Item
{
    using weight_t = std::uint32_t;
    using value_t  = std::uint32_t;

    weight_t weight;
    value_t  value;
};

std::vector<std::size_t> solve_knapsack(const std::vector<Item>& items,
                                        Item::weight_t capacity);

Item::value_t maximum_value(Item::weight_t capacity,
                            const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
