#include "perfect_numbers.h"

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers
{

auto classify(std::int32_t number) -> classification
{
    if (number <= 0)
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    std::int32_t aliquot_sum = 0;
    const std::int32_t upper_bound = (number / 2);

    for (std::int32_t divisor = 1; divisor <= upper_bound; ++divisor)
    {
        if ((number % divisor) == 0)
        {
            aliquot_sum += divisor;
        }
    }

    if (aliquot_sum == number)
    {
        return classification::perfect;
    }
    else if (aliquot_sum > number)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
