#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

static number_t aliquot_sum(number_t n)
{
    number_t sum = 0U;
    for (number_t i = 1U; (i * i) <= n; ++i)
    {
        if ((n % i) == 0U)
        {
            if (i != n)
            {
                sum += i;
            }
            number_t div = n / i;
            if ((div != i) && (div != n))
            {
                sum += div;
            }
        }
    }
    return sum;
}

classification classify(number_t n)
{
    if (n == 0U)
    {
        throw std::domain_error("Zero is not a positive integer");
    }
    // Defensive: handle negative input, even though number_t is unsigned.
    // If user casts a negative int to uint32_t, it will be a large value.
    // But for MISRA, we only check for 0 here, as negative is not possible with uint32_t.

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
