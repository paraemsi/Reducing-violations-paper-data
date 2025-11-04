#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers
{

    auto classify(const std::int32_t n) -> classification
    {
        if (n <= 0)
        {
            throw std::domain_error("Classification is only possible for positive integers.");
        }

        if (n == 1)
        {
            return classification::deficient;
        }

        std::int32_t aliquot_sum {1};

        /*  Widen n once to avoid repeated casts and to prevent overflow
            in the squared-divisor comparison. */
        const std::int64_t n64 {static_cast<std::int64_t>(n)};

        for (std::int32_t divisor {2};
             (static_cast<std::int64_t>(divisor) * static_cast<std::int64_t>(divisor)) <= n64;
             ++divisor)
        {
            if ((n % divisor) == 0)
            {
                const std::int32_t complement {n / divisor};

                aliquot_sum += divisor;

                if (complement != divisor)
                {
                    aliquot_sum += complement;
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
