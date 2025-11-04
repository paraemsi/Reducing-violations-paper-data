#include "perfect_numbers.h"

#include <stdexcept>  // for std::domain_error

namespace perfect_numbers
{

auto classify(std::uint32_t n) -> classification
{
    if (n == static_cast<std::uint32_t>(0U))
    {
        throw std::domain_error("classification is not defined for zero");
    }

    if (n == static_cast<std::uint32_t>(1U))
    {
        return classification::deficient;
    }

    std::uint32_t aliquot_sum = static_cast<std::uint32_t>(1U);

    for (std::uint32_t i = static_cast<std::uint32_t>(2U); i <= (n / i); ++i)
    {
        if ((n % i) == static_cast<std::uint32_t>(0U))
        {
            aliquot_sum += i;

            const std::uint32_t complement = n / i;
            if (complement != i)
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
