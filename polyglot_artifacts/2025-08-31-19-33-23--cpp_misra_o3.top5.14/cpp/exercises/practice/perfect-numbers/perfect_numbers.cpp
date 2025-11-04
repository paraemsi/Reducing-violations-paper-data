#include "perfect_numbers.h"

namespace perfect_numbers {

auto classify(std::uint32_t number) -> classification
{
    if(number == 0U)
    {
        throw std::domain_error("Classification is only defined for positive integers.");
    }

    if(number == 1U)
    {
        return classification::deficient;
    }

    std::uint64_t sum = static_cast<std::uint64_t>(1U);

    for(std::uint32_t divisor = 2U;
        ((static_cast<std::uint64_t>(divisor) * static_cast<std::uint64_t>(divisor)) <=
         static_cast<std::uint64_t>(number));
        ++divisor)
    {
        if((number % divisor) == 0U)
        {
            sum += static_cast<std::uint64_t>(divisor);

            const std::uint32_t paired_divisor =
                static_cast<std::uint32_t>(number / divisor);

            if(paired_divisor != divisor)
            {
                sum += static_cast<std::uint64_t>(paired_divisor);
            }
        }
    }

    if(sum == static_cast<std::uint64_t>(number))
    {
        return classification::perfect;
    }
    else if(sum > static_cast<std::uint64_t>(number))
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

auto classify(std::int32_t number) -> classification
{
    if(number <= 0)
    {
        throw std::domain_error("Classification is only defined for positive integers.");
    }

    /*  Explicit cast justified:
        *  - Delegate to unsigned overload after validating positivity.
        *  - Width is identical (32-bit), conversion unavoidable to reuse logic.
        */
    return classify(static_cast<std::uint32_t>(number));
}

}  // namespace perfect_numbers
