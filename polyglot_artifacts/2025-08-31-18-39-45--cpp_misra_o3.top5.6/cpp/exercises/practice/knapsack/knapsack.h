#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>
#include <cstddef>

namespace knapsack
{

struct Item
{
    std::uint32_t weight;
    std::uint32_t value;
};

/*  Return the maximal attainable total value given the
 *  list of items and the knapsack capacity.               */
auto maximum_value(std::uint32_t            capacity,
                   const std::vector<Item>& items) -> std::uint32_t;

/*  Return the 0-based indices of the items that realise
 *  the optimal value (order corresponds to input order).  */
auto select_items(std::uint32_t            capacity,
                  const std::vector<Item>& items) -> std::vector<std::size_t>;

} // namespace knapsack

#endif // KNAPSACK_H
