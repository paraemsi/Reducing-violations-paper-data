#include "perfect_numbers.h"
#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int32_t n) -> classification {
    if(n <= static_cast<std::int32_t>(0)) {
        throw std::domain_error("Input must be a positive integer.");
    }
    if(n == static_cast<std::int32_t>(1)) {
        return classification::deficient;
    }

    const std::uint32_t un = static_cast<std::uint32_t>(n);

    std::uint64_t sum = static_cast<std::uint64_t>(1ULL);
    std::uint32_t i = static_cast<std::uint32_t>(2U);

    while(((static_cast<std::uint64_t>(i) * static_cast<std::uint64_t>(i)) <= static_cast<std::uint64_t>(un))) {
        if(((un % i) == static_cast<std::uint32_t>(0U))) {
            const std::uint32_t divisor_pair = un / i;
            sum += i;
            if(divisor_pair != i) {
                sum += divisor_pair;
            }
        }
        ++i;
    }

    if(sum == static_cast<std::uint64_t>(un)) {
        return classification::perfect;
    }
    if(sum > static_cast<std::uint64_t>(un)) {
        return classification::abundant;
    }
    return classification::deficient;
}

}  // namespace perfect_numbers
