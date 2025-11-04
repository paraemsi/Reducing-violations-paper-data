#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>

namespace all_your_base {

using big_t   = std::uint64_t;

auto convert(base_t from_base,
             const std::vector<digit_t>& digits,
             base_t to_base) -> std::vector<digit_t>
{
    /* Validate bases */
    if ((from_base < static_cast<base_t>(2U)) ||
        (to_base   < static_cast<base_t>(2U))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    /* Validate digits */
    if (digits.empty()) {
        throw std::invalid_argument("Digits vector must not be empty");
    }

    if ((digits.size() > static_cast<std::size_t>(1U)) &&
        (digits.front() == static_cast<digit_t>(0U))) {
        throw std::invalid_argument("Leading zeros are not permitted");
    }

    for (const digit_t d : digits) {
        if (d >= from_base) {
            throw std::invalid_argument("Digit out of range for source base");
        }
    }

    /* Convert to numeric value */
    big_t value = static_cast<big_t>(0U);
    for (const digit_t d : digits) {
        value = (value * static_cast<big_t>(from_base)) +
                static_cast<big_t>(d);
    }

    /* Zero is a special case */
    if (value == static_cast<big_t>(0U)) {
        return std::vector<digit_t>{static_cast<digit_t>(0U)};
    }

    /* Convert to target base */
    std::vector<digit_t> result{};
    while (value > static_cast<big_t>(0U)) {
        const digit_t remainder =
            static_cast<digit_t>(value % static_cast<big_t>(to_base));
        result.push_back(remainder);
        value = value / static_cast<big_t>(to_base);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
