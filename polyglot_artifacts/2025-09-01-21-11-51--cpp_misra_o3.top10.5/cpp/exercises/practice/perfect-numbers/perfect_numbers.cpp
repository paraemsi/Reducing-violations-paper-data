#include "perfect_numbers.h"

namespace perfect_numbers {

auto classify(std::uint32_t n) noexcept -> classification
{
    /*
     * Aliquot sum calculation:
     *   - Iterate over possible divisors up to sqrt(n) without
     *     using floating-point arithmetic to satisfy MISRA rules.
     *   - Add both divisor and its pair (n / divisor) when appropriate.
     *   - Exclude the number itself from the sum.
     */

    if (n == static_cast<std::uint32_t>(1U))
    {
        return classification::deficient;  // aliquot sum of 1 is 0
    }

    std::uint32_t aliquot_sum{static_cast<std::uint32_t>(0U)};

    for (std::uint32_t i{static_cast<std::uint32_t>(1U)}; i <= (n / i); ++i)
    {
        if ((n % i) == static_cast<std::uint32_t>(0U))
        {
            if (i != n)
            {
                aliquot_sum += i;
            }

            const std::uint32_t paired_divisor{n / i};

            if ((paired_divisor != i) && (paired_divisor != n))
            {
                aliquot_sum += paired_divisor;
            }
        }
    }

    if (aliquot_sum == n)
    {
        return classification::perfect;
    }
    else if (aliquot_sum > n)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
