#include "perfect_numbers.h"

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int64_t n) -> classification
{
    if ((n <= static_cast<std::int64_t>(0))) {
        throw std::domain_error("Classification is only possible for natural numbers.");
    }

    const std::uint64_t n64 = static_cast<std::uint64_t>(n);

    if ((n64 == static_cast<std::uint64_t>(1))) {
        return classification::deficient;
    }

    std::uint64_t sum = static_cast<std::uint64_t>(1);

    for (std::uint64_t d = static_cast<std::uint64_t>(2); (d <= (n64 / d)); ++d) {
        if (((n64 % d) == static_cast<std::uint64_t>(0))) {
            sum = sum + d;
            const std::uint64_t other = n64 / d;
            if ((other != d)) {
                sum = sum + other;
            }
        }
    }

    if ((sum == n64)) {
        return classification::perfect;
    } else {
        if ((sum > n64)) {
            return classification::abundant;
        } else {
            return classification::deficient;
        }
    }
}

}  // namespace perfect_numbers
