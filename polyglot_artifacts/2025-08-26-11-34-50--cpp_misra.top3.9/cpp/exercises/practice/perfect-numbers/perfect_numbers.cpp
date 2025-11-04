#include "perfect_numbers.h"

namespace perfect_numbers {

static number_t aliquot_sum(number_t n)
{
    number_t sum = 0U;
    if (n <= 1U) {
        return 0U;
    }
    for (number_t i = 1U; (i * i) <= n; ++i) {
        if ((n % i) == 0U) {
            number_t div = n / i;
            if ((i != n) && (i != div)) {
                sum = sum + i;
            }
            if ((div != n) && (div != i)) {
                sum = sum + div;
            }
        }
    }
    sum = sum - n + 1U; // Remove n, add 1 (since 1 is always a divisor except for n=1)
    return sum;
}

classification classify(number_t n)
{
    number_t sum = aliquot_sum(n);
    if (sum == n) {
        return perfect;
    } else if (sum > n) {
        return abundant;
    } else {
        return deficient;
    }
}

std::string to_string(classification c)
{
    switch (c) {
        case perfect:
            return "perfect";
        case abundant:
            return "abundant";
        case deficient:
            return "deficient";
        default:
            return "unknown";
    }
}

}  // namespace perfect_numbers
