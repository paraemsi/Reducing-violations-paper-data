#include "perfect_numbers.h"
#include <cstdint>

namespace perfect_numbers
{

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
        // 0 is not classified; could throw or handle as needed
        return classification::deficient;
    }
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
