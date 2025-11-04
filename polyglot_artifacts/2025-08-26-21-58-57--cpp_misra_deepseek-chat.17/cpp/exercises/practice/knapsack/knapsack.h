#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <cstdint>

namespace knapsack
{

struct Item
{
    std::int32_t weight;
    std::int32_t value;
};

std::int32_t maximum_value(std::int32_t maximumWeight, const std::vector<Item>& items);
std::vector<std::uint32_t> selected_items(std::int32_t maximumWeight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
