#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <vector>

namespace knapsack
{

struct Item
{
    int weight;
    int value;
};

/*
 Returns the maximum value that can be put in a knapsack of capacity 'max_weight'.
 'items' is a vector of Item, each with a weight and value.
 Each item can be taken at most once.
*/
int maximum_value(int max_weight, const std::vector<Item>& items);

} // namespace knapsack

#endif // KNAPSACK_H
