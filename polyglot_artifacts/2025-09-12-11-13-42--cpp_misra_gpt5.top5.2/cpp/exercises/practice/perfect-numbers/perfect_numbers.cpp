#include "perfect_numbers.h"

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

namespace
{
    auto aliquot_sum(i64 n) -> i64
    {
        if (n == 1)
        {
            return 0;
        }

        i64 sum = 1;

        for (i64 i = 2; (i <= (n / i)); ++i)
        {
            if ((n % i) == 0)
            {
                sum += i;

                const i64 other = (n / i);
                if (other != i)
                {
                    sum += other;
                }
            }
        }

        return sum;
    }
}  // namespace

classification classify(i64 n)
{
    if (n <= 0)
    {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    const i64 sum = aliquot_sum(n);

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
