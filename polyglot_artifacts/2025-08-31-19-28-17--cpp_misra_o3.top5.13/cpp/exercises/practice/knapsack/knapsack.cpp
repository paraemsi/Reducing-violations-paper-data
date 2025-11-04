#include "knapsack.h"
#include <vector>
#include <cstddef>
#include <cstdint>

namespace knapsack
{

numeric_type maximum_value(numeric_type capacity, const std::vector<Item>& items)
{
    if(capacity <= static_cast<numeric_type>(0))
    {
        return static_cast<numeric_type>(0);
    }

    std::vector<numeric_type> dp(static_cast<std::size_t>(capacity) + static_cast<std::size_t>(1U),
                                 static_cast<numeric_type>(0));

    numeric_type zero_weight_value = static_cast<numeric_type>(0);

    for(const auto& item : items)
    {
        if(item.weight == static_cast<numeric_type>(0))
        {
            zero_weight_value = static_cast<numeric_type>(zero_weight_value + item.value);
            continue;
        }

        numeric_type weight = item.weight;
        numeric_type value  = item.value;

        for(numeric_type c = capacity; (c >= weight); --c)
        {
            numeric_type candidate = value + dp[static_cast<std::size_t>(c - weight)];
            if(candidate > dp[static_cast<std::size_t>(c)])
            {
                dp[static_cast<std::size_t>(c)] = candidate;
            }
        }
    }

    return static_cast<numeric_type>(zero_weight_value + dp[static_cast<std::size_t>(capacity)]);
}

} // namespace knapsack

