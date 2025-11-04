#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int32_t n) -> classification
{
    if (n <= static_cast<std::int32_t>(0)) {
        throw std::domain_error("Classification is only possible for natural numbers.");
    } else {
        // continue
    }

    if (n == static_cast<std::int32_t>(1)) {
        return classification::deficient;
    } else {
        // continue
    }

    std::int64_t sum = static_cast<std::int64_t>(1);

    for (std::int32_t i = static_cast<std::int32_t>(2);
         (static_cast<std::int64_t>(i) * static_cast<std::int64_t>(i)) <= static_cast<std::int64_t>(n);
         ++i) {
        if ((n % i) == static_cast<std::int32_t>(0)) {
            sum = sum + static_cast<std::int64_t>(i);

            const std::int32_t other = static_cast<std::int32_t>(n / i);
            if (other != i) {
                sum = sum + static_cast<std::int64_t>(other);
            } else {
                // no-op
            }
        } else {
            // no divisor
        }
    }

    if (sum == static_cast<std::int64_t>(n)) {
        return classification::perfect;
    } else if (sum > static_cast<std::int64_t>(n)) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

auto classify(std::uint32_t n) -> classification
{
    if (n == static_cast<std::uint32_t>(0U)) {
        throw std::domain_error("Classification is only possible for natural numbers.");
    } else {
        // continue
    }

    if (n == static_cast<std::uint32_t>(1U)) {
        return classification::deficient;
    } else {
        // continue
    }

    std::uint64_t sum = static_cast<std::uint64_t>(1U);

    for (std::uint32_t i = static_cast<std::uint32_t>(2U);
         ((static_cast<std::uint64_t>(i) * static_cast<std::uint64_t>(i)) <= static_cast<std::uint64_t>(n));
         ++i) {
        if ((n % i) == static_cast<std::uint32_t>(0U)) {
            sum = sum + static_cast<std::uint64_t>(i);

            const std::uint32_t other = static_cast<std::uint32_t>(n / i);
            if (other != i) {
                sum = sum + static_cast<std::uint64_t>(other);
            } else {
                // no-op
            }
        } else {
            // no divisor
        }
    }

    if (sum == static_cast<std::uint64_t>(n)) {
        return classification::perfect;
    } else if (sum > static_cast<std::uint64_t>(n)) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}
 
}  // namespace perfect_numbers
