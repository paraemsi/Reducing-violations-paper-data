#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

struct Item
{
    std::uint32_t weight{ 0U };
    std::uint32_t value{ 0U };
};

auto maximum_value(std::uint32_t maximum_weight, std::vector<Item> const& items) noexcept -> std::uint32_t;

} // namespace knapsack

#endif // KNAPSACK_H
