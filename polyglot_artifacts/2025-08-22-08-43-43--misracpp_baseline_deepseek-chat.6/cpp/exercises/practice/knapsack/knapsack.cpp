#include "knapsack.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace knapsack
{

int maximum_value(int maximum_weight, const vector<Item>& items)
{
    if (items.empty()) return 0;
    
    // Initialize DP array
    vector<int> dp(maximum_weight + 1, 0);
    
    for (const auto& item : items)
    {
        // To avoid reusing the same item, we process from the end
        for (int w = maximum_weight; w >= item.weight; --w)
        {
            if (dp[w - item.weight] + item.value > dp[w])
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // Find the maximum value in the dp array up to maximum_weight
    // Since all weights up to maximum_weight are valid
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

