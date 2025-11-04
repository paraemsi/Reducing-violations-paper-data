#include "knapsack.h"
#include <vector>

namespace knapsack
{

auto maximum_value(uint32 capacity, const std::vector<Item>& items) -> uint32
{
    std::vector<uint32> dp(
        capacity + static_cast<uint32>(1U),
        static_cast<uint32>(0U));

    for(const Item& item : items)
    {
        for(uint32 w = capacity; ; )
        {
            if((item.weight <= w))
            {
                const uint32 candidate =
                    (dp[w - item.weight] + item.value);

                if((candidate > dp[w]))
                {
                    dp[w] = candidate;
                }
            }

            if((w == static_cast<uint32>(0U)))
            {
                break;
            }
            --w;
        }
    }

    return dp[capacity];
}

} // namespace knapsack

