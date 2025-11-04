#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <cstddef>     // for std::size_t
#include <cstdint>

namespace knapsack
{

using weight_value_t = std::int32_t;   /* alias – raw type only appears here */

struct Item
{
    weight_value_t weight;
    weight_value_t value;
};

weight_value_t solveKnapsack(const std::vector<Item>& items, weight_value_t maxWeight);

weight_value_t maximum_value(weight_value_t maxWeight, const std::vector<Item>& items);

std::vector<std::size_t> selectItems(const std::vector<Item>& items, weight_value_t maxWeight);

} // namespace knapsack

#endif // KNAPSACK_H
