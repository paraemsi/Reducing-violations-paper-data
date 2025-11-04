#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

/* Fixed-width unsigned integers satisfy MISRA C++ rule set */
struct Item
{
    std::uint32_t weight;
    std::uint32_t value;
};

/*  List of indices of the chosen items (0-based, same order as the
 *  input vector)  */
using index_list_t = std::vector<std::size_t>;

/*  Maximum achievable total value that fits into the knapsack  */
auto max_value(const std::vector<Item>& items,
               std::uint32_t             capacity) -> std::uint32_t;

/*  Solve 0/1 knapsack and return the indices of items to take  */
auto solve(const std::vector<Item>& items,
           std::uint32_t            capacity) -> index_list_t;

/*  Wrapper expected by the tests – takes capacity first, items second.  */
auto maximum_value(std::uint32_t            capacity,
                   const std::vector<Item>& items) -> std::uint32_t;

} // namespace knapsack

#endif // KNAPSACK_H
