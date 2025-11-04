#include "knapsack.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace knapsack
{

int maximum_value(int maximum_weight, const vector<Item>& items)
{
    if (items.empty()) return 0;
    
    // dp[w] = maximum value with weight w
    vector<int> dp(maximum_weight + 1, 0);
    
    for (const auto& item : items)
    {
        // To avoid reusing the same item, process from the end
        for (int w = maximum_weight; w >= item.weight; --w)
        {
            if (dp[w - item.weight] + item.value > dp[w])
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // Find the maximum value in all dp entries
    // Since dp[w] is always non-decreasing? Not necessarily, but we can find the max
    int max_value = 0;
    for (int w = 0; w <= maximum_weight; ++w)
    {
        if (dp[w] > max_value)
        {
            max_value = dp[w];
        }
    }
    return max_value;
}

} // namespace knapsack

