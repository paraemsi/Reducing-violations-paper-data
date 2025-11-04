#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <cstdint>
#include <vector>

#if defined(__cplusplus) && (__cplusplus >= 201703L)
#define KNAPSACK_NODISCARD [[nodiscard]]
#else
#define KNAPSACK_NODISCARD
#endif

namespace knapsack
{

struct Item
{
    std::int32_t weight{0};
    std::int32_t value{0};
};

KNAPSACK_NODISCARD auto maximum_value(std::int32_t capacity, const std::vector<Item>& items) noexcept -> std::int32_t;
KNAPSACK_NODISCARD auto maximumValue(std::int32_t capacity, const std::vector<Item>& items) noexcept -> std::int32_t;

} // namespace knapsack

#endif // KNAPSACK_H
