#include "knapsack.h"
#include <vector>
#include <cstdint>
#include <cstddef>

namespace knapsack
{

[[nodiscard]] uint32 max_value(const std::vector<Item>& items, uint32 capacity)
{
    const std::size_t cap = static_cast<std::size_t>(capacity);
    std::vector<uint32> dp(cap + static_cast<std::size_t>(1U), static_cast<uint32>(0U));

    for(const Item& item : items)
    {
        const std::size_t weight = static_cast<std::size_t>(item.weight);

        if(weight > cap)
        {
            continue;
        }

        for(int64 c = static_cast<int64>(cap); c >= static_cast<int64>(weight); --c)
        {
            const uint32 without_item = dp[static_cast<std::size_t>(c)];
            const uint32 with_item =
                static_cast<uint32>(dp[static_cast<std::size_t>(c) - weight] + item.value);

            dp[static_cast<std::size_t>(c)] = ((with_item > without_item) ? with_item : without_item);
        }
    }

    return dp[cap];
}

[[nodiscard]] uint32 maximum_value(uint32 capacity, const std::vector<Item>& items)
{
    return max_value(items, capacity);
}

} // namespace knapsack

