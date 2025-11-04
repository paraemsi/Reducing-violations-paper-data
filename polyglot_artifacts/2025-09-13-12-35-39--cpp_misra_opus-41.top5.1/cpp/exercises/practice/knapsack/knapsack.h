#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>

namespace knapsack
{

// Type aliases for better readability and MISRA compliance
// Using long to ensure at least 32-bit range on all platforms
using weight_t = long;
using value_t = long;

struct Item
{
    weight_t weight;
    value_t value;
};

value_t maximum_value(weight_t maximum_weight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
