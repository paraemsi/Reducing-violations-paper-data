#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <cstdint>
#include <vector>

namespace knapsack
{

struct Item
{
    /* default-initialised to zero for safety */
    std::int32_t weight {};
    std::int32_t value {};
};

[[nodiscard]] auto maximum_value(std::int32_t maximum_weight,
                                 const std::vector<Item> & items) noexcept -> std::int32_t;

} // namespace knapsack

#endif // KNAPSACK_H
