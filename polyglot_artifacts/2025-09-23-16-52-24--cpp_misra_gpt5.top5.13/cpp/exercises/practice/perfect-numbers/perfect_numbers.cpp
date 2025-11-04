#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

classification classify(std::int64_t n)
{
    if (n <= 0)
    {
        throw std::domain_error("Classification is only possible for natural numbers.");
    }

    if (n == 1)
    {
        return classification::deficient;
    }

    std::int64_t sum = 1;
    std::int64_t d = 2;

    while (d <= (n / d))
    {
        if ((n % d) == 0)
        {
            const std::int64_t q = (n / d);
            sum = (sum + d);
            if (q != d)
            {
                sum = (sum + q);
            }
        }
        ++d;
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
