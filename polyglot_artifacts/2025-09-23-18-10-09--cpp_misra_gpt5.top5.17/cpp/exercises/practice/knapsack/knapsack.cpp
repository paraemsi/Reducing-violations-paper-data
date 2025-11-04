#include "knapsack.h"

#include <cstddef>
#include <cstdint>
#include <vector>

namespace knapsack
{

auto maximum_value(std::size_t max_weight, const std::vector<Item>& items) -> std::size_t
{
    if ((max_weight == static_cast<std::size_t>(0)) || (items.empty()))
    {
        return static_cast<std::size_t>(0);
    }

    std::size_t capacity = max_weight;

    const std::size_t cap_size = capacity;

    std::vector<std::size_t> dp(cap_size + static_cast<std::size_t>(1), static_cast<std::size_t>(0));

    for (const Item& it : items)
    {
        if ((it.weight == static_cast<std::size_t>(0)) || (it.value == static_cast<std::size_t>(0)))
        {
            continue;
        }

        if (it.weight > capacity)
        {
            continue;
        }

        const std::size_t w_item = it.weight;
        const std::size_t val_item = it.value;

        for (std::size_t w = cap_size; w >= w_item; --w)
        {
            const std::size_t with_item = (dp[w - w_item] + val_item);
            const std::size_t without_item = dp[w];
            dp[w] = ((with_item > without_item) ? with_item : without_item);
        }
    }

    return dp[cap_size];
}

} // namespace knapsack

