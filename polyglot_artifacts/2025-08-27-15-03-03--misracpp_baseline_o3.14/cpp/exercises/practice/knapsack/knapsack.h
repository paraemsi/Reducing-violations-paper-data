#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <vector>
#include <cstddef>  // for std::size_t if needed in future extensions

namespace knapsack
{

struct Item
{
    int weight;
    int value;
};
int maximum_value(int capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
