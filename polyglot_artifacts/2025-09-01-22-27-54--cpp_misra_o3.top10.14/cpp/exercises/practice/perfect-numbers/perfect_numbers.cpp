#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int64_t number) -> classification
{
    if (number <= static_cast<std::int64_t>(0))
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    std::int64_t aliquot_sum{0};

    for (std::int64_t i{1}; i <= (number / i); ++i)
    {
        if ((number % i) == static_cast<std::int64_t>(0))
        {
            std::int64_t complement{number / i};

            if (i != number)
            {
                aliquot_sum += i;
            }

            if ((complement != i) && (complement != number))
            {
                aliquot_sum += complement;
            }
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
