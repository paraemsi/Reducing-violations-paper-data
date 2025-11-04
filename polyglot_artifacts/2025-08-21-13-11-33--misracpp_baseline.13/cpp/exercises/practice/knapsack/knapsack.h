#ifndef KNAPSACK_H
#define KNAPSACK_H

namespace knapsack
{

struct Item
{
    int weight;
    int value;
};
int knapsackMaxValue(const Item* items, int itemCount, int maxWeight, bool* taken);
} // namespace knapsack

#endif // KNAPSACK_H

} // namespace knapsack

#endif // KNAPSACK_H
