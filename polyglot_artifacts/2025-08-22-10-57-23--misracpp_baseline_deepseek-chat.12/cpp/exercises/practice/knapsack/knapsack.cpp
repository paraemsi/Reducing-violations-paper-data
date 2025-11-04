#include "knapsack.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace knapsack
{

int maximum_value(int maximum_weight, const vector<Item>& items)
{
    if (items.empty() || maximum_weight == 0) return 0;
    
    // Create a DP array where dp[w] stores the maximum value for weight w
    vector<int> dp(maximum_weight + 1, 0);
    
    for (const auto& item : items)
    {
        // Process from the end to prevent reusing the same item
        for (int w = maximum_weight; w >= item.weight; --w)
        {
            if (dp[w - item.weight] + item.value > dp[w])
            {
                dp[w] = dp[w - item.weight] + item.value;
            }
        }
    }
    
    // Find the maximum value in the dp array
    return *max_element(dp.begin(), dp.end());
}

} // namespace knapsack

