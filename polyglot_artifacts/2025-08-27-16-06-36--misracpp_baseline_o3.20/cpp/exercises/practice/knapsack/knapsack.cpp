#include "knapsack.h"

#include <algorithm>
#include <vector>

namespace knapsack
{

int maximum_value(int capacity, const std::vector<Item>& items)
{
    if (capacity <= 0 || items.empty())
    {
        return 0;
    }

    // dp[w] will hold the maximum value for weight limit w
    std::vector<int> dp(static_cast<std::size_t>(capacity) + 1, 0);

    for (const auto& item : items)
    {
        // Traverse weights in reverse to avoid re-using the same item
        for (int w = capacity; w >= item.weight; --w)
        {
            dp[w] = std::max(dp[w], dp[w - item.weight] + item.value);
        }
    }

    return dp[capacity];
}

} // namespace knapsack


