#include "knapsack.h"
#include <cstddef>

namespace knapsack
{

namespace
{
    inline auto solve_knapsack(std::int32_t capacity, const std::vector<Item>& items) noexcept -> std::int32_t
    {
        if ((capacity <= static_cast<std::int32_t>(0)) || (items.empty())) {
            return static_cast<std::int32_t>(0);
        }

        const std::uint32_t cap_u = static_cast<std::uint32_t>(capacity);
        const std::size_t cap = static_cast<std::size_t>(cap_u);
        std::vector<std::int32_t> dp(cap + static_cast<std::size_t>(1U), static_cast<std::int32_t>(0));

        for (const Item& item : items) {
            if ((item.weight <= static_cast<std::int32_t>(0)) || (item.value <= static_cast<std::int32_t>(0))) {
                continue;
            }

            const std::uint32_t weight_u = static_cast<std::uint32_t>(item.weight);
            if (static_cast<std::size_t>(weight_u) > cap) {
                continue;
            }

            for (std::uint64_t w = static_cast<std::uint64_t>(cap_u);
                 w >= static_cast<std::uint64_t>(weight_u);
                 --w) {
                const std::size_t wi = static_cast<std::size_t>(static_cast<std::uint32_t>(w));
                const std::uint64_t prev_u64 = (w - static_cast<std::uint64_t>(weight_u));
                const std::size_t prev = static_cast<std::size_t>(static_cast<std::uint32_t>(prev_u64));
                const std::int32_t with_item = (dp[prev] + item.value);
                if (with_item > dp[wi]) {
                    dp[wi] = with_item;
                }
            }
        }

        return dp[cap];
    }
} // unnamed namespace

auto maximum_value(std::int32_t capacity, const std::vector<Item>& items) noexcept -> std::int32_t
{
    return solve_knapsack(capacity, items);
}

auto maximumValue(std::int32_t capacity, const std::vector<Item>& items) noexcept -> std::int32_t
{
    return solve_knapsack(capacity, items);
}

} // namespace knapsack

