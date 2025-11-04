#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int64_t number) -> classification
{
    if (number <= static_cast<std::int64_t>(0))
    {
        throw std::domain_error("Classification is undefined for non-positive integers.");
    }

    if (number == static_cast<std::int64_t>(1))
    {
        return classification::deficient;
    }

    const std::uint64_t u_number = static_cast<std::uint64_t>(number);

    std::uint64_t aliquot_sum = static_cast<std::uint64_t>(1U);

    for (std::uint64_t divisor = static_cast<std::uint64_t>(2U);
         (divisor * divisor) <= u_number;
         ++divisor)
    {
        if ((u_number % divisor) == static_cast<std::uint64_t>(0U))
        {
            aliquot_sum = static_cast<std::uint64_t>(aliquot_sum + divisor);
            const std::uint64_t paired = static_cast<std::uint64_t>(u_number / divisor);
            if (paired != divisor)
            {
                aliquot_sum = static_cast<std::uint64_t>(aliquot_sum + paired);
            }
        }
    }

    if (aliquot_sum == u_number)
    {
        return classification::perfect;
    }
    else
    {
        if (aliquot_sum > u_number)
        {
            return classification::abundant;
        }
        else
        {
            return classification::deficient;
        }
    }
}

}  // namespace perfect_numbers
