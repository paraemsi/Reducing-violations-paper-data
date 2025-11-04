#include "perfect_numbers.h"
#include <cstdint>
#include <stdexcept>

namespace perfect_numbers
{

auto classify(const std::int32_t number) -> classification
{
    /*  Non-positive values are outside Nicomachus' scheme.                           */
    if(number <= static_cast<std::int32_t>(0))
    {
        throw std::domain_error("classification is undefined for non-positive integers");
    }

    const std::uint32_t number_u = static_cast<std::uint32_t>(number);

    /*  Special-case 1 early – its aliquot sum is 0.                                 */
    std::uint64_t aliquot_sum = static_cast<std::uint64_t>(1U);
    if(number_u == static_cast<std::uint32_t>(1U))
    {
        aliquot_sum = static_cast<std::uint64_t>(0U);
    }
    else
    {
        for(std::uint32_t divisor = static_cast<std::uint32_t>(2U);
            (static_cast<std::uint64_t>(divisor) * static_cast<std::uint64_t>(divisor)) <=
                static_cast<std::uint64_t>(number_u);
            ++divisor)
        {
            if((number_u % divisor) == static_cast<std::uint32_t>(0U))
            {
                const std::uint32_t complement = number_u / divisor;

                aliquot_sum += static_cast<std::uint64_t>(divisor);

                if(complement != divisor)
                {
                    aliquot_sum += static_cast<std::uint64_t>(complement);
                }
            }
        }
    }

    if(aliquot_sum == static_cast<std::uint64_t>(number_u))
    {
        return classification::perfect;
    }
    else if(aliquot_sum > static_cast<std::uint64_t>(number_u))
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
