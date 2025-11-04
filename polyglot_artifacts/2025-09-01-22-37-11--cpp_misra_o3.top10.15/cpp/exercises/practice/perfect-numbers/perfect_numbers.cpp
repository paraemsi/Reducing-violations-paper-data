#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int32_t n) -> classification
{
    if (n <= static_cast<std::int32_t>(0))
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    if (n == static_cast<std::int32_t>(1))
    {
        return classification::deficient;
    }

    std::int64_t sum{static_cast<std::int64_t>(1)};

    for (std::int32_t divisor{static_cast<std::int32_t>(2)};
         (static_cast<std::int64_t>(divisor) * static_cast<std::int64_t>(divisor)) <=
             static_cast<std::int64_t>(n);
         ++divisor)
    {
        if ((n % divisor) == static_cast<std::int32_t>(0))
        {
            sum += divisor;

            const std::int32_t counterpart{n / divisor};
            if (counterpart != divisor)
            {
                sum += counterpart;
            }
        }
    }

    if (sum == static_cast<std::int64_t>(n))
    {
        return classification::perfect;
    }
    else if (sum > static_cast<std::int64_t>(n))
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
