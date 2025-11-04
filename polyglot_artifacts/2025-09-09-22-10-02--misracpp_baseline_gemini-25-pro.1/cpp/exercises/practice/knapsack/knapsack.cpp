#include "knapsack.h"

#include <algorithm>
#include <vector>

namespace knapsack
{

Result maximum_value(int maximum_weight, const std::vector<Item>& items) {
    if (maximum_weight < 0) {
        maximum_weight = 0;
    }

    int base_value = 0;
    std::vector<size_t> zero_weight_indices;
    std::vector<Item> heavy_items;
    std::vector<size_t> heavy_items_original_indices;

    for (size_t i = 0; i < items.size(); ++i) {
        if (items[i].weight == 0) {
            base_value += items[i].value;
            zero_weight_indices.push_back(i);
        } else if (items[i].weight > 0) {
            heavy_items.push_back(items[i]);
            heavy_items_original_indices.push_back(i);
        }
    }

    const auto n = heavy_items.size();
    if (n == 0 || maximum_weight == 0) {
        return {base_value, zero_weight_indices};
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(maximum_weight + 1, 0));

    for (size_t i = 1; i <= n; ++i) {
        const auto& item = heavy_items[i - 1];
        for (int w = 1; w <= maximum_weight; ++w) {
            if (item.weight <= w) {
                dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - item.weight] + item.value);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    Result result;
    result.value = base_value + dp[n][maximum_weight];
    result.item_indices = zero_weight_indices;

    int w = maximum_weight;
    for (size_t i = n; i > 0; --i) {
        if (dp[i][w] != dp[i-1][w]) {
            result.item_indices.push_back(heavy_items_original_indices[i - 1]);
            w -= heavy_items[i-1].weight;
        }
    }
    std::sort(result.item_indices.begin(), result.item_indices.end());

    return result;
}

} // namespace knapsack

