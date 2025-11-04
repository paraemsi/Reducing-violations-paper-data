#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

classification classify(number_t n)
{
    if (n <= static_cast<number_t>(0))
    {
        throw std::domain_error("number must be positive");
    }

    if (n == static_cast<number_t>(1))
    {
        return classification::deficient;
    }

    number_t sum = static_cast<number_t>(1);

    for (number_t i = static_cast<number_t>(2); (i <= (n / i)); ++i)
    {
        if ((n % i) == static_cast<number_t>(0))
        {
            const number_t other = n / i;

            sum = sum + i;

            if (other != i)
            {
                sum = sum + other;
            }
            else
            {
                // No action required
            }
        }
        else
        {
            // No action required
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
