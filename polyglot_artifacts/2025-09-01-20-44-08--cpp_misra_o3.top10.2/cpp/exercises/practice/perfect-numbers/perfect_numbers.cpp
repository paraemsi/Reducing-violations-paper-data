#include "perfect_numbers.h"

#include <cmath>
#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

auto classify(std::int32_t value) -> classification
{
    if (value <= static_cast<std::int32_t>(0)) {
        throw std::domain_error(
            "Classification is only possible for positive integers.");
    }

    if (value == static_cast<std::int32_t>(1)) {
        return classification::deficient;
    }

    const std::uint32_t u_value{static_cast<std::uint32_t>(value)};
    std::uint64_t       aliquot_sum{1U};

    const double        root{
        std::sqrt(static_cast<double>(u_value))};
    const std::uint32_t upper_limit{
        static_cast<std::uint32_t>(root)};

    for (std::uint32_t divisor{2U}; divisor <= upper_limit; ++divisor) {
        if ((u_value % divisor) == static_cast<std::uint32_t>(0U)) {
            const std::uint32_t complement{
                static_cast<std::uint32_t>(u_value / divisor)};
            aliquot_sum += static_cast<std::uint64_t>(divisor);
            if (complement != divisor) {
                aliquot_sum += static_cast<std::uint64_t>(complement);
            }
        }
    }

    if (aliquot_sum == static_cast<std::uint64_t>(u_value)) {
        return classification::perfect;
    }

    if (aliquot_sum > static_cast<std::uint64_t>(u_value)) {
        return classification::abundant;
    }

    return classification::deficient;
}

}  // namespace perfect_numbers
