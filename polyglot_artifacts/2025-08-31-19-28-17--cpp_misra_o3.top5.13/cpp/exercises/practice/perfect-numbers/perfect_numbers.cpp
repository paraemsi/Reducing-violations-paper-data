#include "perfect_numbers.h"

namespace perfect_numbers {

auto classify(std::uint32_t n) -> classification
{
    if(n == 0U)
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    /* Compute aliquot sum (sum of proper divisors).           */
    std::uint64_t sum{0U};

    for(std::uint32_t i{1U}; (static_cast<std::uint64_t>(i) * static_cast<std::uint64_t>(i)) <= static_cast<std::uint64_t>(n); ++i)
    {
        if((n % i) == 0U)
        {
            const std::uint32_t other{n / i};

            if(i != n)
            {
                sum += static_cast<std::uint64_t>(i);
            }

            if((other != i) && (other != n))
            {
                sum += static_cast<std::uint64_t>(other);
            }
        }
    }

    if(sum == static_cast<std::uint64_t>(n))
    {
        return classification::perfect;
    }
    else if(sum > static_cast<std::uint64_t>(n))
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}   // namespace perfect_numbers
