#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

struct Item
{
    std::int64_t weight;
    std::int64_t value;
};

std::int64_t maximum_value(std::int64_t capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
