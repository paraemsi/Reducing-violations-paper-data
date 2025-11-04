#include "perfect_numbers.h"

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

namespace
{
    auto aliquot_sum(std::int32_t n) -> std::int64_t
    {
        if (n == 1)
        {
            return 0LL;
        }

        std::int64_t sum = 1LL;
        const std::int64_t n64 = static_cast<std::int64_t>(n);

        for (std::int32_t d = 2; ((static_cast<std::int64_t>(d) * static_cast<std::int64_t>(d)) <= n64); ++d)
        {
            if (((n % d) == 0))
            {
                sum += static_cast<std::int64_t>(d);

                const std::int32_t q = (n / d);
                if (q != d)
                {
                    sum += static_cast<std::int64_t>(q);
                }
            }
        }

        return sum;
    }
}  // namespace

auto classify(std::int32_t n) -> classification
{
    if (n <= 0)
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    const std::int64_t sum = aliquot_sum(n);
    const std::int64_t n64 = static_cast<std::int64_t>(n);

    if (sum == n64)
    {
        return classification::perfect;
    }
    else if (sum > n64)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}


}  // namespace perfect_numbers
