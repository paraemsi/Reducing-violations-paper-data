#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

auto classify(integer_t n) -> classification
{
    if (n <= 0)
    {
        throw std::domain_error("Classification is only defined for positive integers");
    }

    if (n == 1)
    {
        return classification::deficient;
    }

    integer_t sum = 1;

    for (integer_t i = 2; i <= (n / i); ++i)
    {
        if ((n % i) == 0)
        {
            sum = (sum + i);

            const integer_t pair = (n / i);
            if (pair != i)
            {
                sum = (sum + pair);
            }
        }
    }

    if (sum == n)
    {
        return classification::perfect;
    }
    else if (sum > n)
    {
        return classification::abundant;
    }
    else
    {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
