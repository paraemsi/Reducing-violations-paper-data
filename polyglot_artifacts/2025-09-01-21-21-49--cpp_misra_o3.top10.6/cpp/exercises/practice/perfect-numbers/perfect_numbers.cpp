#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

[[nodiscard]] auto classify(std::int32_t n) -> classification
{
    /* Reject non-positive integers */
    if (n <= static_cast<std::int32_t>(0)) {
        throw std::domain_error("Classification is only defined for positive integers");
    }

    if (n == static_cast<std::int32_t>(1)) {
        return classification::deficient;
    }

    std::int32_t aliquot_sum = static_cast<std::int32_t>(1);

    for (std::int32_t i = static_cast<std::int32_t>(2); i <= (n / i); ++i) {
        if ((n % i) == static_cast<std::int32_t>(0)) {
            aliquot_sum += i;

            const std::int32_t pair_divisor = n / i;
            if (pair_divisor != i) {
                aliquot_sum += pair_divisor;
            }
        }
    }

    if (aliquot_sum == n) {
        return classification::perfect;
    } else if (aliquot_sum > n) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
