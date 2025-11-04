#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

static auto aliquot_sum(std::int64_t n) -> std::int64_t
{
    // Precondition: n > 0
    if ((n == static_cast<std::int64_t>(1))) {
        return static_cast<std::int64_t>(0);
    }

    std::int64_t sum = static_cast<std::int64_t>(1);
    std::int64_t i = static_cast<std::int64_t>(2);

    while ((i <= (n / i))) {
        if (((n % i) == static_cast<std::int64_t>(0))) {
            const std::int64_t complement = (n / i);
            if ((i == complement)) {
                sum = (sum + i);
            } else {
                sum = (sum + (i + complement));
            }
        }
        i = (i + static_cast<std::int64_t>(1));
    }

    return sum;
}

auto classify(std::int64_t value) -> classification
{
    if ((value <= static_cast<std::int64_t>(0))) {
        throw std::domain_error("classification is only defined for positive integers");
    }

    const std::int64_t sum = aliquot_sum(value);
    if ((sum == value)) {
        return classification::perfect;
    } else {
        if ((sum > value)) {
            return classification::abundant;
        } else {
            return classification::deficient;
        }
    }
}

}  // namespace perfect_numbers
