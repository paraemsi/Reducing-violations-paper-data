#include "perfect_numbers.h"
#include <stdexcept>  // for std::domain_error
#include <cstdint>

namespace perfect_numbers {

static auto classify_positive(std::uint32_t number) -> classification
{
    if(number == static_cast<std::uint32_t>(0U))
    {
        throw std::domain_error("Classification is only defined for positive integers.");
    }

    std::uint64_t aliquot_sum{0U};

    for(std::uint32_t i{1U}; i <= (number / i); ++i)
    {
        if((number % i) == static_cast<std::uint32_t>(0U))
        {
            if(i != number)
            {
                aliquot_sum += static_cast<std::uint64_t>(i);
            }

            const std::uint32_t paired_factor{number / i};

            if((paired_factor != i) && (paired_factor != number))
            {
                aliquot_sum += static_cast<std::uint64_t>(paired_factor);
            }
        }
    }

    if(static_cast<std::uint64_t>(number) == aliquot_sum)
    {
        return classification::perfect;
    }
    else if(static_cast<std::uint64_t>(number) < aliquot_sum)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}  // function classify

auto classify(std::int32_t number) -> classification
{
    if(number <= static_cast<std::int32_t>(0))
    {
        throw std::domain_error("Classification is only defined for positive integers.");
    }

    /*  The cast is safe because the value is known to be positive and within the
        range representable by std::uint32_t (test inputs are small). */
    return classify_positive(static_cast<std::uint32_t>(number));
}  // overload for signed input

}  // namespace perfect_numbers
