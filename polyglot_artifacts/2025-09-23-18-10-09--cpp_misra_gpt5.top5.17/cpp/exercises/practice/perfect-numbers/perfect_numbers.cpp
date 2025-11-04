#include "perfect_numbers.h"

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

classification classify(std::int64_t n)
{
    if ((n <= 0))
    {
        throw std::domain_error("Only natural numbers can be classified.");
    }

    if ((n == 1))
    {
        return classification::deficient;
    }

    std::int64_t sum = 1;

    for (std::int64_t d = 2; (d <= (n / d)); ++d)
    {
        if (((n % d) == 0))
        {
            sum = sum + d;
            const std::int64_t other = n / d;
            if ((other != d))
            {
                sum = sum + other;
            }
        }
    }

    if ((sum == n))
    {
        return classification::perfect;
    }
    else
    {
        if ((sum > n))
        {
            return classification::abundant;
        }
        else
        {
            return classification::deficient;
        }
    }
}

classification classify(std::uint64_t n)
{
    if ((n == static_cast<std::uint64_t>(0)))
    {
        throw std::domain_error("Only natural numbers can be classified.");
    }

    if ((n == static_cast<std::uint64_t>(1)))
    {
        return classification::deficient;
    }

    std::uint64_t sum = static_cast<std::uint64_t>(1);

    for (std::uint64_t d = static_cast<std::uint64_t>(2); (d <= (n / d)); ++d)
    {
        if (((n % d) == static_cast<std::uint64_t>(0)))
        {
            sum = sum + d;
            const std::uint64_t other = n / d;
            if ((other != d))
            {
                sum = sum + other;
            }
        }
    }

    if ((sum == n))
    {
        return classification::perfect;
    }
    else
    {
        if ((sum > n))
        {
            return classification::abundant;
        }
        else
        {
            return classification::deficient;
        }
    }
}

}  // namespace perfect_numbers
