#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

auto classify(std::uint32_t n) -> Classification
{
    if(n == static_cast<std::uint32_t>(0u))
    {
        throw std::domain_error("Classification is undefined for zero.");
    }

    if(n == static_cast<std::uint32_t>(1u))
    {
        return Classification::deficient;
    }

    /* Use 64-bit accumulator to avoid overflow while summing divisors */
    std::uint64_t aliquot_sum = static_cast<std::uint64_t>(1u);

    /* Iterate up to square root of n */
    for(std::uint32_t i = static_cast<std::uint32_t>(2u);
        (static_cast<std::uint64_t>(i) * static_cast<std::uint64_t>(i)) <= static_cast<std::uint64_t>(n);
        ++i)
    {
        if((n % i) == static_cast<std::uint32_t>(0u))
        {
            aliquot_sum += static_cast<std::uint64_t>(i);

            const std::uint32_t complementary_divisor = static_cast<std::uint32_t>(n / i);

            if(complementary_divisor != i)
            {
                aliquot_sum += static_cast<std::uint64_t>(complementary_divisor);
            }
        }
    }

    if(aliquot_sum == static_cast<std::uint64_t>(n))
    {
        return Classification::perfect;
    }
    else if(aliquot_sum > static_cast<std::uint64_t>(n))
    {
        return Classification::abundant;
    }
    else
    {
        return Classification::deficient;
    }
}

}   // namespace perfect_numbers
