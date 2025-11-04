#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int32_t number) -> classification
{
    if(number <= static_cast<std::int32_t>(0))
    {
        throw std::domain_error("Classification is only defined for positive integers.");
    }

    std::int32_t aliquot_sum{static_cast<std::int32_t>(0)};

    for(std::int32_t divisor{static_cast<std::int32_t>(1)}; divisor <= (number / static_cast<std::int32_t>(2)); ++divisor)
    {
        if((number % divisor) == static_cast<std::int32_t>(0))
        {
            aliquot_sum += divisor;
        }
    }

    if(aliquot_sum == number)
    {
        return classification::perfect;
    }
    if(aliquot_sum > number)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
