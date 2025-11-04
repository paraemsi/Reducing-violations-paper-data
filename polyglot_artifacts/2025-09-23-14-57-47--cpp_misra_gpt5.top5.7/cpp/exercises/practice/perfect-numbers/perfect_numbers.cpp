#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int64_t n) -> classification
{
    if ((n <= static_cast<std::int64_t>(0))) {
        throw std::domain_error("n must be a positive integer");
    }

    if ((n == static_cast<std::int64_t>(1))) {
        return classification::deficient;
    }

    std::int64_t sum = static_cast<std::int64_t>(1);
    std::int64_t d = static_cast<std::int64_t>(2);

    while ((d <= (n / d))) {
        if (((n % d) == static_cast<std::int64_t>(0))) {
            sum = (sum + d);
            const std::int64_t other = (n / d);
            if ((other != d)) {
                sum = (sum + other);
            }
        }
        d = (d + static_cast<std::int64_t>(1));
    }

    if ((sum == n)) {
        return classification::perfect;
    } else if ((sum > n)) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
