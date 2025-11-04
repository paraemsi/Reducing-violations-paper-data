#include "knapsack.h"

#include <algorithm>
#include <cstddef>
#include <vector>

namespace knapsack
{

std::uint64_t maximum_value(std::uint32_t maximum_weight,
                          const std::vector<Item>& items)
{
    std::uint64_t zero_weight_items_value{0ULL};
    std::uint64_t total_weight{0ULL};
    for (const Item& item : items)
    {
        if (item.weight == 0U)
        {
            zero_weight_items_value += item.value;
        }
        else
        {
            total_weight += item.weight;
        }
    }

    const std::uint32_t effective_maximum_weight{static_cast<std::uint32_t>(
        std::min(static_cast<std::uint64_t>(maximum_weight), total_weight))};

    std::vector<std::uint64_t> dp(
        static_cast<std::size_t>(effective_maximum_weight) + 1U, 0ULL);

    for (const Item& item : items)
    {
        if (item.weight > 0U)
        {
            for (std::uint32_t w{effective_maximum_weight}; w >= item.weight; --w)
            {
                std::size_t current_w_idx{static_cast<std::size_t>(w)};
                std::size_t remaining_w_idx{
                    static_cast<std::size_t>(w - item.weight)};
                dp[current_w_idx] = std::max(
                    dp[current_w_idx], (dp[remaining_w_idx] + item.value));
            }
        }
    }

    return dp[static_cast<std::size_t>(effective_maximum_weight)] +
           zero_weight_items_value;
}

} // namespace knapsack

