#include "perfect_numbers.h"

#include <cstdint>

namespace perfect_numbers
{

auto classify(std::int32_t value) -> classification
{
    if(value <= static_cast<std::int32_t>(0))
    {
        throw std::domain_error("Value must be a positive integer");
    }

    if(value == static_cast<std::int32_t>(1))
    {
        return classification::deficient;
    }

    /* Use 64-bit signed accumulator to avoid overflow when summing divisors */
    std::int64_t aliquot_sum = static_cast<std::int64_t>(1);

    for(std::int32_t i = static_cast<std::int32_t>(2);
        (static_cast<std::int64_t>(i) * static_cast<std::int64_t>(i)) <= static_cast<std::int64_t>(value);
        ++i)
    {
        if((value % i) == static_cast<std::int32_t>(0))
        {
            aliquot_sum += static_cast<std::int64_t>(i);

            const std::int32_t pair_divisor = static_cast<std::int32_t>(value / i);
            if(i != pair_divisor)
            {
                aliquot_sum += static_cast<std::int64_t>(pair_divisor);
            }
        }
    }

    if(aliquot_sum == static_cast<std::int64_t>(value))
    {
        return classification::perfect;
    }
    else if(aliquot_sum > static_cast<std::int64_t>(value))
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
