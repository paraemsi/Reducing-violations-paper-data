#include "knapsack.h"
#include <vector>
#include <algorithm>

namespace knapsack
{

int maximum_value(int max_weight, const std::vector<Item>& items)
{
    int n = static_cast<int>(items.size());
    // dp[w] = max value for weight limit w
    std::vector<int> dp(max_weight + 1, 0);

    for (int i = 0; i < n; ++i) {
        // Traverse backwards to avoid using the same item more than once
        for (int w = max_weight; w >= items[i].weight; --w) {
            dp[w] = std::max(dp[w], dp[w - items[i].weight] + items[i].value);
        }
    }
    return dp[max_weight];
}

} // namespace knapsack

