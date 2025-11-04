#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

auto classify(const std::int64_t n) -> classification
{
    if (n <= static_cast<std::int64_t>(0))
    {
        throw std::domain_error("Classification is only defined for positive integers");
    }

    const std::uint64_t un{static_cast<std::uint64_t>(n)};

    std::uint64_t sum{static_cast<std::uint64_t>(1U)};

    if (un == static_cast<std::uint64_t>(1U))
    {
        sum = static_cast<std::uint64_t>(0U);
    }
    else
    {
        /* Avoid potential overflow from (i * i) by using division */
        for (std::uint64_t i{static_cast<std::uint64_t>(2U)}; i <= (un / i); ++i)
        {
            if ((un % i) == static_cast<std::uint64_t>(0U))
            {
                sum = static_cast<std::uint64_t>(sum + i);

                const std::uint64_t other_divisor{static_cast<std::uint64_t>(un / i)};
                if (other_divisor != i)
                {
                    sum = static_cast<std::uint64_t>(sum + other_divisor);
                }
            }
        }
    }

    if (sum == un)
    {
        return classification::perfect;
    }
    else if (sum > un)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
