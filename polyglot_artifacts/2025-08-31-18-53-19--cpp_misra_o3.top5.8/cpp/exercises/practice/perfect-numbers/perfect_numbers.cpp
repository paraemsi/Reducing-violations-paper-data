#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers
{
    auto classify(std::int32_t n) -> classification
    {
        if(n <= static_cast<std::int32_t>(0))
        {
            throw std::domain_error("Classification is only defined for positive integers");
        }

        const std::uint32_t un{static_cast<std::uint32_t>(n)};

        /* The aliquot sum of 1 is 0 by definition */
        std::uint32_t sum{static_cast<std::uint32_t>((un == static_cast<std::uint32_t>(1U)) ? 0U : 1U)};

        /* Use division in the loop condition to avoid potential overflow in
         * (i * i) when i is large. */
        for(std::uint32_t i{static_cast<std::uint32_t>(2U)}; i <= (un / i); ++i)
        {
            if((un % i) == static_cast<std::uint32_t>(0U))
            {
                sum = static_cast<std::uint32_t>(sum + i);

                const std::uint32_t paired_divisor{static_cast<std::uint32_t>(un / i)};
                if(paired_divisor != i)
                {
                    sum = static_cast<std::uint32_t>(sum + paired_divisor);
                }
            }
        }

        if(sum == un)
        {
            return classification::perfect;
        }
        else if(sum > un)
        {
            return classification::abundant;
        }
        else
        {
            return classification::deficient;
        }
    }
}  // namespace perfect_numbers
