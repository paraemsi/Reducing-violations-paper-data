#include "perfect_numbers.h"

namespace perfect_numbers {

auto classify(std::int64_t number) -> classification
{
    if(number <= static_cast<std::int64_t>(0))
    {
        throw std::domain_error("Classification is only possible for positive integers");
    }

    if(number == static_cast<std::int64_t>(1))
    {
        return classification::deficient;
    }

    std::int64_t aliquot_sum {static_cast<std::int64_t>(1)};
    for(std::int64_t i {static_cast<std::int64_t>(2)};
        (i <= (number / i));
        ++i)
    {
        if((number % i) == static_cast<std::int64_t>(0))
        {
            aliquot_sum += i;
            const std::int64_t paired_factor {number / i};
            if(paired_factor != i)
            {
                aliquot_sum += paired_factor;
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
