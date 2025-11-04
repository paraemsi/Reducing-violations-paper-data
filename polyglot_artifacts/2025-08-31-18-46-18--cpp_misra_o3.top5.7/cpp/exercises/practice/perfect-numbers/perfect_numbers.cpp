#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers
{
    /*  Internal helper – not exposed via the public header. */
    static auto classify_number(std::uint32_t value) -> classification
    {
        if (value == static_cast<std::uint32_t>(0U))
        {
            throw std::domain_error("Classification is only defined for positive integers");
        }

        std::uint32_t aliquot_sum{static_cast<std::uint32_t>(0U)};

        /*  Use division to avoid the potential for overflow when squaring `i`.   */
        for (std::uint32_t i{static_cast<std::uint32_t>(1U)}; i <= (value / i); ++i)
        {
            if ((value % i) == static_cast<std::uint32_t>(0U))
            {
                if (i != value)
                {
                    aliquot_sum += i;
                }

                const std::uint32_t paired_divisor{value / i};

                if ((paired_divisor != i) && (paired_divisor != value))
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

    auto classify(std::int32_t value) -> classification
    {
        if (value <= static_cast<std::int32_t>(0))
        {
            throw std::domain_error("Classification is only defined for positive integers");
        }

        /* static_cast is acceptable here as the value is guaranteed to be positive
           and fits within the range of std::uint32_t. */
        return classify_number(static_cast<std::uint32_t>(value));
    }
} // namespace perfect_numbers
