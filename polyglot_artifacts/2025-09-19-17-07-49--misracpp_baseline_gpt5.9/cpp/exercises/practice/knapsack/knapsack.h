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

 // Returns the maximum total value achievable without exceeding the given capacity.
 // Uses 0/1 knapsack (each item can be taken at most once).
int maximum_value(int capacity, const std::vector<Item>& items) noexcept;

} // namespace knapsack

#endif // KNAPSACK_H
