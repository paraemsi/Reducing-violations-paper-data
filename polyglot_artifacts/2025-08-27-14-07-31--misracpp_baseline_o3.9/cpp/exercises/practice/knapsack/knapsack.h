#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <cstddef>   // for std::size_t

namespace knapsack
{

struct Item
{
    int weight;
    int value;
};

/*
 * Compute the maximum total value attainable with the given weight limit.
 * @param max_weight  Maximum weight capacity of the knapsack (non-negative).
 * @param items       Vector of items, each with a weight and value.
 * @return            Maximum total value achievable.
 */
[[nodiscard]] int maximum_value(int max_weight, const std::vector<Item>& items);

/*
 * Solve the classic 0/1 knapsack problem.
 * @param items       Vector of items, each with a weight and value.
 * @param max_weight  Maximum weight capacity of the knapsack (non-negative).
 * @return            Indices of the items chosen (ordered as in the input).
 */
[[nodiscard]] std::vector<std::size_t> select_items(const std::vector<Item>& items, int max_weight);

} // namespace knapsack

#endif // KNAPSACK_H
