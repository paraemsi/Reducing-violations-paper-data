#include "perfect_numbers.h"

#include <stdexcept>

namespace perfect_numbers {

auto classify(std::uint32_t n) -> classification
{
    if (n == 0U) {
        throw std::domain_error("Classification is undefined for zero.");
    }

    if (n == 1U) {
        return classification::deficient;
    }

    std::uint32_t sum{1U};

    for (std::uint32_t i{2U}; (i * i) <= n; ++i) {
        if ((n % i) == 0U) {
            sum += i;
            const std::uint32_t complement{n / i};
            if (complement != i) {
                sum += complement;
            }
        }
    }

    if (sum == n) {
        return classification::perfect;
    } else if (sum > n) {
        return classification::abundant;
    } else {
        return classification::deficient;
    }
}

}  // namespace perfect_numbers
