#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <cstdint>
#include <vector>

namespace knapsack
{

struct Item
{
    std::int32_t weight{0};
    std::int32_t value{0};
};

// Compute the maximum total value achievable without exceeding maximum_weight.
// Uses 0/1 knapsack dynamic programming.
std::int32_t maximum_value(std::int32_t maximum_weight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
