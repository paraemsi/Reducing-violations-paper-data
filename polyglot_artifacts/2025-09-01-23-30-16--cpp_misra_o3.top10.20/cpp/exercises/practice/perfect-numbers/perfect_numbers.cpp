#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers
{

auto classify(std::uint32_t number) -> Classification
{
    if(number == static_cast<std::uint32_t>(0U))
    {
        throw std::invalid_argument("Number must be positive");
    }

    if(number == static_cast<std::uint32_t>(1U))
    {
        return Classification::deficient;
    }

    std::uint64_t sum = static_cast<std::uint64_t>(1ULL);

    for(std::uint32_t divisor = static_cast<std::uint32_t>(2U);
        divisor <= (number / divisor);
        ++divisor)
    {
        if((number % divisor) == static_cast<std::uint32_t>(0U))
        {
            const std::uint32_t paired_divisor = number / divisor;
            sum += static_cast<std::uint64_t>(divisor);
            if(paired_divisor != divisor)
            {
                sum += static_cast<std::uint64_t>(paired_divisor);
            }
        }
    }

    if(sum == static_cast<std::uint64_t>(number))
    {
        return Classification::perfect;
    }
    else if(sum > static_cast<std::uint64_t>(number))
    {
        return Classification::abundant;
    }
    else
    {
        return Classification::deficient;
    }
}

} // namespace perfect_numbers
