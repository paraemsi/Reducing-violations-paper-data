#include "perfect_numbers.h"

#include <stdexcept>
#include <cstdint>

namespace perfect_numbers {

auto classify(std::uint32_t n) -> classification {
    if (n == 0U) {
        throw std::domain_error("Classification is only possible for natural numbers.");
    }

    if (n == 1U) {
        return classification::deficient;
    }

    std::uint64_t sum = 1ULL;

    for (std::uint32_t i = 2U; (i <= (n / i)); ++i) {
        if ((n % i) == 0U) {
            sum += static_cast<std::uint64_t>(i);
            const std::uint32_t d = n / i;
            if (d != i) {
                sum += static_cast<std::uint64_t>(d);
            }
        }
    }

    const std::uint64_t nn = static_cast<std::uint64_t>(n);

    if (sum == nn) {
        return classification::perfect;
    } else if (sum > nn) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

auto classify(std::int32_t n) -> classification {
    if (n <= 0) {
        throw std::domain_error("Classification is only possible for natural numbers.");
    }

    if (n == 1) {
        return classification::deficient;
    }

    std::int64_t sum = static_cast<std::int64_t>(1);

    for (std::int32_t i = 2; (i <= (n / i)); ++i) {
        if ((n % i) == 0) {
            sum += static_cast<std::int64_t>(i);
            const std::int32_t d = n / i;
            if (d != i) {
                sum += static_cast<std::int64_t>(d);
            }
        }
    }

    const std::int64_t nn = static_cast<std::int64_t>(n);

    if (sum == nn) {
        return classification::perfect;
    } else if (sum > nn) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
