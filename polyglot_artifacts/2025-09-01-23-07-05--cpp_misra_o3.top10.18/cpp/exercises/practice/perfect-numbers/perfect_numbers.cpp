#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers
{

auto classify(uint64 n) -> classification
{
    if(n == static_cast<uint64>(0U))
    {
        throw std::domain_error("Classification is only defined for positive integers");
    }

    uint64 sum = static_cast<uint64>(1U);

    if(n == static_cast<uint64>(1U))
    {
        sum = static_cast<uint64>(0U);
    }
    else
    {
        for(uint64 i = static_cast<uint64>(2U); ((i * i) <= n); ++i)
        {
            if((n % i) == static_cast<uint64>(0U))
            {
                sum += i;
                const uint64 other = n / i;
                if(other != i)
                {
                    sum += other;
                }
            }
        }
    }

    if(sum == n)
    {
        return classification::perfect;
    }
    else if(sum > n)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
