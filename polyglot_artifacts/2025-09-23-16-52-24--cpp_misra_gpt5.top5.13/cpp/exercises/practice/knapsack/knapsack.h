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

 // Compute the maximum total value that can be carried without exceeding max_weight.
std::int32_t maximum_value(std::int32_t max_weight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
