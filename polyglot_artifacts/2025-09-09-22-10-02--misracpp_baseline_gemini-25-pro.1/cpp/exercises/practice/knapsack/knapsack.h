#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <cstddef>

namespace knapsack
{

struct Item
{
    int weight;
    int value;
};

struct Result
{
    int value;
    std::vector<size_t> item_indices;
};

inline bool operator==(const Result& lhs, int rhs) {
    return lhs.value == rhs;
}

inline bool operator==(int lhs, const Result& rhs) {
    return lhs == rhs.value;
}

Result maximum_value(int maximum_weight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
