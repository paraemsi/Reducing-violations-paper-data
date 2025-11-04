#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int32_t number) -> classification
{
    if (number <= static_cast<std::int32_t>(0))
    {
        throw std::domain_error("number must be positive");
    }

    if (number == static_cast<std::int32_t>(1))
    {
        return classification::deficient;
    }

    std::int32_t sum {static_cast<std::int32_t>(1)};

    for (std::int32_t divisor {static_cast<std::int32_t>(2)};
         ((static_cast<std::int64_t>(divisor) * static_cast<std::int64_t>(divisor)) <= static_cast<std::int64_t>(number));
         ++divisor)
    {
        if ((number % divisor) == static_cast<std::int32_t>(0))
        {
            std::int32_t complement {number / divisor};

            sum = sum + divisor;

            if (complement != divisor)
            {
                sum = sum + complement;
            }
        }
    }

    if (sum == number)
    {
        return classification::perfect;
    }
    else if (sum > number)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
