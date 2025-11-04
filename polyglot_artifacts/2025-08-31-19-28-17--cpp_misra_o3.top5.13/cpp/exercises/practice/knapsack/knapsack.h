#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

using numeric_type = std::int32_t;

struct Item
{
    numeric_type weight;
    numeric_type value;
};

numeric_type maximum_value(numeric_type capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
