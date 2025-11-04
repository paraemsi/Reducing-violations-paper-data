#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

[[nodiscard]] auto classify(int_type n) -> classification
{
    if(n <= int_type{0})
    {
        throw std::domain_error{"Classification is only defined for positive integers"};
    }

    const auto un{static_cast<uint_type>(n)};             /* positive, safe to convert */

    uint_type aliquot_sum{uint_type{0}};

    for(uint_type i{uint_type{1}}; i <= (un / uint_type{2}); ++i)
    {
        if((un % i) == uint_type{0})
        {
            aliquot_sum += i;
        }
    }

    if(aliquot_sum == un)
    {
        return classification::perfect;
    }
    else if(aliquot_sum > un)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
