#include "perfect_numbers.h"

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int64_t n) -> classification
{
    if ((n <= static_cast<std::int64_t>(0))) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    // Handle n == 1 explicitly: aliquot sum is 0
    if ((n == static_cast<std::int64_t>(1))) {
        return classification::deficient;
    }

    std::int64_t sum{static_cast<std::int64_t>(1)};
    for (std::int64_t i{static_cast<std::int64_t>(2)}; ((i <= (n / i))); ++i) {
        if (((n % i) == static_cast<std::int64_t>(0))) {
            sum = (sum + i);
            const std::int64_t pair_divisor{(n / i)};
            if ((pair_divisor != i)) {
                sum = (sum + pair_divisor);
            }
        }
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
