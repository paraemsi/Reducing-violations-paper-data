#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int64_t value) -> classification
{
    if (value <= static_cast<std::int64_t>(0))
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    /* Special-case 1 because its aliquot sum is 0. */
    if (value == static_cast<std::int64_t>(1))
    {
        return classification::deficient;
    }

    std::int64_t aliquot_sum {static_cast<std::int64_t>(1)};

    for (std::int64_t divisor {static_cast<std::int64_t>(2)};
         (divisor <= (value / divisor));
         ++divisor)
    {
        if ((value % divisor) == static_cast<std::int64_t>(0))
        {
            aliquot_sum += divisor;

            const std::int64_t complement {(value / divisor)};

            if (complement != divisor)
            {
                aliquot_sum += complement;
            }
        }
    }

    if (aliquot_sum == value)
    {
        return classification::perfect;
    }
    else if (aliquot_sum > value)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
