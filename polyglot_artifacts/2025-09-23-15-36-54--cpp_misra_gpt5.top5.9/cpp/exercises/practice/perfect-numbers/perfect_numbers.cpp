#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

[[nodiscard]] classification classify(std::int64_t value)
{
    if (value <= 0)
    {
        throw std::domain_error("Classification is only possible for natural numbers.");
    }

    if (value == 1)
    {
        return classification::deficient;
    }

    std::int64_t sum = 1;

    for (std::int64_t i = 2; ((i * i) <= value); ++i)
    {
        if ((value % i) == 0)
        {
            const std::int64_t other = value / i;

            sum = sum + i;

            if (other != i)
            {
                sum = sum + other;
            }
        }
    }

    if (sum == value)
    {
        return classification::perfect;
    }
    else
    {
        if (sum > value)
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
