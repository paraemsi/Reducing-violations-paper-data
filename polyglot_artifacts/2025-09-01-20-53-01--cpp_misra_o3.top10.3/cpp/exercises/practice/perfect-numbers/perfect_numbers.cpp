#include "perfect_numbers.h"
#include <cmath>
#include <stdexcept>
#include <limits>

namespace perfect_numbers {

static auto classify_impl(std::uint32_t number) -> classification
{
    if (number == static_cast<std::uint32_t>(0U))
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    if (number == static_cast<std::uint32_t>(1U))
    {
        return classification::deficient;
    }

    std::uint64_t aliquot_sum = static_cast<std::uint64_t>(1U);
    const std::uint32_t limit =
        static_cast<std::uint32_t>(std::sqrt(static_cast<double>(number)));

    for (std::uint32_t i = static_cast<std::uint32_t>(2U); i <= limit; ++i)
    {
        if ((number % i) == static_cast<std::uint32_t>(0U))
        {
            aliquot_sum += static_cast<std::uint64_t>(i);

            const std::uint32_t paired_divisor =
                static_cast<std::uint32_t>(number / i);

            if (paired_divisor != i)
            {
                aliquot_sum += static_cast<std::uint64_t>(paired_divisor);
            }
        }
    }

    if (aliquot_sum == static_cast<std::uint64_t>(number))
    {
        return classification::perfect;
    }
    else if (aliquot_sum > static_cast<std::uint64_t>(number))
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

auto classify(std::int32_t number) -> classification
{
    if (number <= static_cast<std::int32_t>(0))
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    return classify_impl(static_cast<std::uint32_t>(number));
}

auto classify(std::int64_t number) -> classification
{
    if (number <= static_cast<std::int64_t>(0))
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    if (number <= static_cast<std::int64_t>(std::numeric_limits<std::uint32_t>::max()))
    {
        return classify_impl(static_cast<std::uint32_t>(number));
    }

    const std::uint64_t u_number = static_cast<std::uint64_t>(number);
    std::uint64_t aliquot_sum   = static_cast<std::uint64_t>(1U);

    const std::uint64_t limit =
        static_cast<std::uint64_t>(std::sqrt(static_cast<double>(u_number)));

    for (std::uint64_t i = static_cast<std::uint64_t>(2U); i <= limit; ++i)
    {
        if ((u_number % i) == static_cast<std::uint64_t>(0U))
        {
            aliquot_sum += i;

            const std::uint64_t paired_divisor = u_number / i;

            if (paired_divisor != i)
            {
                aliquot_sum += paired_divisor;
            }
        }
    }

    if (aliquot_sum == u_number)
    {
        return classification::perfect;
    }
    else if (aliquot_sum > u_number)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
