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

using item = Item;
using Items = std::vector<Item>;

// Compute the maximum total value achievable with the given capacity using 0/1 knapsack.
int maximum_value(int capacity, const Items& items);

} // namespace knapsack

#endif // KNAPSACK_H
