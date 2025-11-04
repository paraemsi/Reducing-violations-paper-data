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

auto knapsack_max_value(const std::vector<Item>& items,
                        std::int32_t max_weight) -> std::int32_t;

auto maximum_value(std::int32_t max_weight,
                   const std::vector<Item>& items) -> std::int32_t;

} // namespace knapsack

#endif // KNAPSACK_H
