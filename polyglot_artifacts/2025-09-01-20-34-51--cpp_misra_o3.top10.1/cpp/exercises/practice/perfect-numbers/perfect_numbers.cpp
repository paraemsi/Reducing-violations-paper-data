#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int32_t number) -> classification
{
    if(number <= static_cast<std::int32_t>(0))
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    if(number == static_cast<std::int32_t>(1))
    {
        return classification::deficient;
    }

    std::int32_t aliquot_sum{static_cast<std::int32_t>(1)};

    for(std::int32_t i{static_cast<std::int32_t>(2)};
        (i <= (number / i));
        ++i)
    {
        if((number % i) == static_cast<std::int32_t>(0))
        {
            std::int32_t other_divisor{number / i};

            aliquot_sum += i;

            if((other_divisor != i) && (other_divisor != number))
            {
                aliquot_sum += other_divisor;
            }
        }
    }

    if(aliquot_sum == number)
    {
        return classification::perfect;
    }
    else if(aliquot_sum > number)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
