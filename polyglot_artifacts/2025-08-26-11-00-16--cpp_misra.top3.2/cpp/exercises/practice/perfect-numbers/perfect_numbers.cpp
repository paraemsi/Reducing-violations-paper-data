#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

static number_t aliquot_sum(number_t n)
{
    if (n <= static_cast<number_t>(1))
    {
        return static_cast<number_t>(0);
    }
    number_t sum = static_cast<number_t>(1);
    for (number_t i = static_cast<number_t>(2); (i * i) <= n; ++i)
    {
        if ((n % i) == static_cast<number_t>(0))
        {
            if (i == (n / i))
            {
                sum = (sum + i);
            }
            else
            {
                sum = (sum + i + (n / i));
            }
        }
    }
    return sum;
}

classification classify(number_t n)
{
    if (n == static_cast<number_t>(0))
    {
        throw std::domain_error("Zero is not a positive integer");
    }
    // Defensive: handle negative input, even though number_t is unsigned
    // (if called with a negative int cast to uint32_t, it will be a large value)
    // But the test expects only positive integers, so we only check for zero.

    number_t sum = aliquot_sum(n);
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
