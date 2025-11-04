#include "perfect_numbers.h"
#include <cstdint>
#include <stdexcept>

namespace perfect_numbers
{

auto classify(std::uint32_t n) -> classification
{
    if (n == static_cast<std::uint32_t>(0U))
    {
        throw std::domain_error("classification is only defined for positive integers");
    }

    if (n == static_cast<std::uint32_t>(1U))
    {
        return classification::deficient;
    }

    std::uint64_t sum{static_cast<std::uint64_t>(1U)};

    for (std::uint32_t i{2U}; (i <= (n / i)); ++i)
    {
        if ((n % i) == static_cast<std::uint32_t>(0U))
        {
            sum += static_cast<std::uint64_t>(i);

            std::uint32_t complement{n / i};
            if (complement != i)
            {
                sum += static_cast<std::uint64_t>(complement);
            }
        }
    }

    if (sum == static_cast<std::uint64_t>(n))
    {
        return classification::perfect;
    }
    else
    {
        if (sum > static_cast<std::uint64_t>(n))
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
