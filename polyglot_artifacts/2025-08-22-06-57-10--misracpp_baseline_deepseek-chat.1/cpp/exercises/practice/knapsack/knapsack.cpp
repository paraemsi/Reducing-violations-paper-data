#include "knapsack.h"
#include <vector>
#include <algorithm>
using namespace std;

namespace knapsack
{

int maximum_value(int maximum_weight, const vector<Item>& items)
{
    int n = items.size();
    if (n == 0 || maximum_weight <= 0)
        return 0;
    
    // Use a 1D DP array to save space
    vector<int> dp(maximum_weight + 1, 0);
    
    for (int i = 0; i < n; i++)
    {
        const Item& item = items[i];
        // Update from the end to prevent reusing the same item
        for (int w = maximum_weight; w >= item.weight; w--)
        {
            dp[w] = max(dp[w], dp[w - item.weight] + item.value);
        }
    }
    
    // Find the maximum value in the dp array
    // Since all values are positive, the maximum value will be at dp[maximum_weight]
    // But to be safe, we can find the maximum in the entire array
    int max_value = 0;
    for (int w = 0; w <= maximum_weight; w++)
    {
        max_value = max(max_value, dp[w]);
    }
    return max_value;
}

} // namespace knapsack

