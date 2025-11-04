#ifndef EXERCISM_KNAPSACK_H_INCLUDED
#define EXERCISM_KNAPSACK_H_INCLUDED

#include <vector>

namespace knapsack
{

struct Item
{
    int weight;
    int value;
};

int maximum_value(int capacity, const std::vector<Item>& items);

} // namespace knapsack

#endif // EXERCISM_KNAPSACK_H_INCLUDED
