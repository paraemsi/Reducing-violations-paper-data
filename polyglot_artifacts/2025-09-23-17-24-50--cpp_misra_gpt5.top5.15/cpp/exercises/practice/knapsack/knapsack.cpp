#include "knapsack.h"

#include <algorithm>
#include <vector>

namespace knapsack
{

value_t maximum_value(weight_t capacity, const std::vector<Item>& items) noexcept
{
    const std::size_t cap_size = static_cast<std::size_t>(capacity);
    std::vector<value_t> dp(cap_size + static_cast<std::size_t>(1U), static_cast<value_t>(0U));

    for (const Item& it : items)
    {
        const value_t v = it.value;
        const std::size_t w_size = static_cast<std::size_t>(it.weight);

        if (w_size == static_cast<std::size_t>(0U))
        {
            for (std::size_t j = static_cast<std::size_t>(0U); j < (cap_size + static_cast<std::size_t>(1U)); ++j)
            {
                dp[j] = static_cast<value_t>(dp[j] + v);
            }
        }
        else
        {
            for (std::size_t j = (cap_size + static_cast<std::size_t>(1U)); j > w_size; --j)
            {
                const std::size_t idx = (j - static_cast<std::size_t>(1U));
                const std::size_t prev_idx = (idx - w_size);
                const value_t candidate = static_cast<value_t>(dp[prev_idx] + v);
                if (candidate > dp[idx])
                {
                    dp[idx] = candidate;
                }
            }
        }
    }

    return dp[cap_size];
}

std::vector<std::size_t> choose_items(weight_t capacity, const std::vector<Item>& items)
{
    const std::size_t n = items.size();
    const std::size_t cap_size = static_cast<std::size_t>(capacity);

    std::vector<std::vector<value_t>> dp(
        (n + static_cast<std::size_t>(1U)),
        std::vector<value_t>(cap_size + static_cast<std::size_t>(1U), static_cast<value_t>(0U)));

    for (std::size_t i = static_cast<std::size_t>(1U); i < (n + static_cast<std::size_t>(1U)); ++i)
    {
        const Item& it = items[i - static_cast<std::size_t>(1U)];
        const value_t v = it.value;
        const std::size_t w_size = static_cast<std::size_t>(it.weight);

        for (std::size_t w = static_cast<std::size_t>(0U); w < (cap_size + static_cast<std::size_t>(1U)); ++w)
        {
            const value_t not_take = dp[i - static_cast<std::size_t>(1U)][w];
            value_t best = not_take;

            if (w >= w_size)
            {
                const value_t take = static_cast<value_t>(
                    dp[i - static_cast<std::size_t>(1U)][w - w_size] + v);
                if (take > best)
                {
                    best = take;
                }
            }

            dp[i][w] = best;
        }
    }

    // Reconstruct chosen items (indices)
    std::vector<std::size_t> chosen{};
    std::size_t w = cap_size;
    for (std::size_t i = n; i > static_cast<std::size_t>(0U); --i)
    {
        if (dp[i][w] != dp[i - static_cast<std::size_t>(1U)][w])
        {
            const std::size_t idx = (i - static_cast<std::size_t>(1U));
            chosen.push_back(idx);

            const std::size_t w_size = static_cast<std::size_t>(items[idx].weight);
            if (w >= w_size)
            {
                w = (w - w_size);
            }
            else
            {
                // Should not happen, but keep safe guard
                w = static_cast<std::size_t>(0U);
            }
        }
        else
        {
            // not taken; nothing to do
        }
    }

    std::reverse(chosen.begin(), chosen.end());
    return chosen;
}

} // namespace knapsack

