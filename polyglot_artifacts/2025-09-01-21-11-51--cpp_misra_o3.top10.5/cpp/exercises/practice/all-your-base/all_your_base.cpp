#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

auto convert(std::uint32_t   from_base,
             const digits_t& input_digits,
             std::uint32_t   to_base) -> digits_t
{
    /* Validate bases */
    if ((from_base < static_cast<std::uint32_t>(2U)) || (to_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    /* Handle empty input: represents the value zero */
    if (input_digits.empty()) {
        return digits_t{static_cast<digit_t>(0U)};
    }

    /* Validate digits */
    for (const digit_t digit : input_digits) {
        if (digit >= from_base) {
            throw std::invalid_argument("Digit out of range for source base");
        }
    }

    /* Convert input digits to an integer value (use 64-bit to minimise overflow risk) */
    std::uint64_t value = static_cast<std::uint64_t>(0U);
    for (const digit_t digit : input_digits) {
        value = ((value * static_cast<std::uint64_t>(from_base)) + static_cast<std::uint64_t>(digit));
    }

    /* Special-case zero */
    if (value == static_cast<std::uint64_t>(0U)) {
        return digits_t{static_cast<digit_t>(0U)};
    }

    /* Convert integer value to target base */
    digits_t result{};
    while (value > static_cast<std::uint64_t>(0U)) {
        const digit_t remainder =
            static_cast<digit_t>(value % static_cast<std::uint64_t>(to_base));
        result.push_back(remainder);
        value = value / static_cast<std::uint64_t>(to_base);
    }

    /* Digits are produced least-significant first; reverse to most-significant first */
    std::reverse(result.begin(), result.end());

    return result;
}

}  // namespace all_your_base
