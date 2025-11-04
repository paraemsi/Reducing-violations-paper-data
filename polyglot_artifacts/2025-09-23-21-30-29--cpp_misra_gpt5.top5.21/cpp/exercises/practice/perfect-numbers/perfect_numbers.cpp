#include "perfect_numbers.h"
#include <stdexcept>
#include <cinttypes>

namespace {


auto compute_aliquot_sum_signed(std::int64_t n) -> std::int64_t
{
    if ((n <= INT64_C(1)))
    {
        return INT64_C(0);
    }

    std::int64_t sum = INT64_C(1);

    for (std::int64_t i = INT64_C(2); (i <= (n / i)); ++i)
    {
        if (((n % i) == INT64_C(0)))
        {
            sum = sum + i;

            const std::int64_t other = n / i;
            if ((other != i))
            {
                sum = sum + other;
            }
        }
    }

    return sum;
}


}  // namespace

namespace perfect_numbers {

classification classify(std::int64_t n)
{
    if ((n <= INT64_C(0)))
    {
        throw std::domain_error("Classification is only possible for natural numbers.");
    }

    if ((n == INT64_C(1)))
    {
        return classification::deficient;
    }

    const std::int64_t nn = n;
    const std::int64_t sum = compute_aliquot_sum_signed(nn);

    if ((sum == nn))
    {
        return classification::perfect;
    }
    else
    {
        if ((sum > nn))
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
