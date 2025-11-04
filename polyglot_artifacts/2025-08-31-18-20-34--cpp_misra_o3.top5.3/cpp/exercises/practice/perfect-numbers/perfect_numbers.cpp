#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

[[nodiscard]] auto classify(std::uint32_t value) -> classification
{
    if (value == static_cast<std::uint32_t>(0U)) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }

    if (value == static_cast<std::uint32_t>(1U)) {
        return classification::deficient;
    }

    const std::uint64_t n64 = static_cast<std::uint64_t>(value);
    std::uint64_t sum = static_cast<std::uint64_t>(1U);

    for (std::uint64_t i = static_cast<std::uint64_t>(2U);
         (i * i) <= n64;
         ++i) {
        if ((n64 % i) == static_cast<std::uint64_t>(0U)) {
            sum += i;
            const std::uint64_t pair_divisor = n64 / i;
            if (pair_divisor != i) {
                sum += pair_divisor;
            }
        }
    }

    if (sum == n64) {
        return classification::perfect;
    } else if (sum > n64) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

[[nodiscard]] auto classify(std::int32_t value) -> classification
{
    if ((value <= static_cast<std::int32_t>(0))) {
        throw std::domain_error("Classification is only possible for positive integers.");
    }
    return classify(static_cast<std::uint32_t>(value));
}

}  // namespace perfect_numbers
