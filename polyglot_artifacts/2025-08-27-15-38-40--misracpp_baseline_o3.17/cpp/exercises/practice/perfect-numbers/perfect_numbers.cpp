#include "perfect_numbers.h"

namespace perfect_numbers {

static std::int64_t aliquot_sum(std::int64_t n)
{
    if (n == 1) {
        return 0;          // 1 has no proper divisors
    }

    std::int64_t sum{1};   // 1 is a proper divisor of every n > 1
    for (std::int64_t d{2}; d <= n / d; ++d) {
        if (n % d == 0) {
            sum += d;
            std::int64_t other = n / d;
            if (other != d) {
                sum += other;  // avoid double-adding square root divisor
            }
        }
    }
    return sum;
}

classification classify(std::int64_t n)
{
    if (n <= 0) {
        throw std::domain_error{"classification is only defined for positive integers"};
    }

    auto sum = aliquot_sum(n);

    if (sum == n) {
        return classification::perfect;
    }
    if (sum > n) {
        return classification::abundant;
    }
    return classification::deficient;
}

}  // namespace perfect_numbers
