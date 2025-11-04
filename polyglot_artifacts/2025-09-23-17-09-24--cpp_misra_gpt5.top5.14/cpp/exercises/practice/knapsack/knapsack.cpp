#include "knapsack.h"
#include <cstdint>
#include <cstddef>
#include <vector>

namespace knapsack
{

auto maximum_value(std::uint32_t maximum_weight, std::vector<Item> const& items) noexcept -> std::uint32_t
{
    std::uint32_t const cap = maximum_weight;
    std::uint32_t const cap_plus_one = static_cast<std::uint32_t>(cap + static_cast<std::uint32_t>(1U));
    std::size_t const dp_size = static_cast<std::size_t>(cap_plus_one);
    std::vector<std::uint32_t> dp(dp_size, static_cast<std::uint32_t>(0U));

    for (std::size_t idx = static_cast<std::size_t>(0); (idx < items.size()); ++idx)
    {
        Item const& it = items[idx];

        if ((it.value == static_cast<std::uint32_t>(0U)))
        {
            {
                // Skip items with zero value
            }
        }
        else
        {
            std::uint32_t const w = it.weight;
            std::uint32_t const v = it.value;

            if ((w <= cap))
            {
                std::uint32_t j = cap;
                while (true)
                {
                    std::uint32_t const without_item = dp[static_cast<std::size_t>(j)];
                    std::uint32_t const with_item = dp[static_cast<std::size_t>(j - w)] + v;

                    if ((with_item > without_item))
                    {
                        dp[static_cast<std::size_t>(j)] = with_item;
                    }
                    else
                    {
                        {
                            // No update needed
                        }
                    }

                    if (j == w)
                    {
                        break;
                    }
                    --j;
                }
            }
            else
            {
                {
                    // Item too heavy; skip
                }
            }
        }
    }

    return dp[static_cast<std::size_t>(cap)];
}

} // namespace knapsack

