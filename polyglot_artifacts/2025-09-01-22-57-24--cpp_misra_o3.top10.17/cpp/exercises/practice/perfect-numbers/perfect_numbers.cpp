#include "perfect_numbers.h"

namespace perfect_numbers {

[[nodiscard]] auto classify(std::int32_t number) -> classification
{
    /*------------------------------------------------------------------
     * Promote to 64-bit for all calculations to avoid overflow while
     * still keeping the public interface a 32-bit signed integer that
     * matches the exercise test-suite.
     *-----------------------------------------------------------------*/
    const std::int64_t value = static_cast<std::int64_t>(number);

    if (value <= static_cast<std::int64_t>(0))
    {
        throw std::domain_error("Classification is undefined for zero or negative integers.");
    }

    if (value == static_cast<std::int64_t>(1))
    {
        return classification::deficient;
    }

    std::int64_t aliquot_sum = static_cast<std::int64_t>(0);

    /*------------------------------------------------------------------
     * Iterate up to sqrt(number) without using floating-point arithmetic.
     * For every divisor found, add both divisor and paired quotient,
     * taking care not to add the number itself or duplicate a square root.
     *-----------------------------------------------------------------*/
    for (std::int64_t divisor = static_cast<std::int64_t>(1);
         divisor <= (value / divisor);
         ++divisor)
    {
        if ((value % divisor) == static_cast<std::int64_t>(0))
        {
            /* divisor is a factor */
            if (divisor != value)
            {
                aliquot_sum += divisor;
            }

            const std::int64_t paired_divisor = value / divisor;

            if ((paired_divisor != divisor) && (paired_divisor != value))
            {
                aliquot_sum += paired_divisor;
            }
        }
    }

    if (aliquot_sum == value)
    {
        return classification::perfect;
    }
    else if (aliquot_sum > value)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}   // namespace perfect_numbers
