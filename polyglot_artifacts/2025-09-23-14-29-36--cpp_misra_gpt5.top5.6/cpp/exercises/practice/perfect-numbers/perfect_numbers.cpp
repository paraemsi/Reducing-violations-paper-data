#include "perfect_numbers.h"

#include <stdexcept>
#include <cstdint>

namespace perfect_numbers {

auto classify(std::int64_t n) -> classification
{
    if ((n <= 0))
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    if ((n == 1))
    {
        return classification::deficient;
    }

    std::int64_t sum = 1;

    for (std::int64_t i = 2; (i <= (n / i)); ++i)
    {
        if (((n % i) == 0))
        {
            sum += i;

            const std::int64_t other = (n / i);
            if ((other != i))
            {
                sum += other;
            }
        }
    }

    if ((sum == n))
    {
        return classification::perfect;
    }
    else if ((sum > n))
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
