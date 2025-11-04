#include "all_your_base.h"

#include <algorithm>     // for std::reverse
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace all_your_base {

auto convert(base_t                       from_base,
             const std::vector<digit_t>&  digits,
             base_t                       to_base) -> std::vector<digit_t>
{
    /* Preconditions ------------------------------------------------------- */
    if ((from_base < 2) || (to_base < 2)) {
        throw std::invalid_argument("Bases must be ≥ 2");
    }

    if (digits.empty()) {
        throw std::invalid_argument("Input digit sequence must not be empty");
    }

    for (const digit_t digit : digits) {
        if (digit >= static_cast<digit_t>(from_base)) {
            throw std::invalid_argument("Digit out of range for from_base");
        }
    }

    /* Handle value zero early -------------------------------------------- */
    bool is_zero {true};
    for (const digit_t digit : digits) {
        if (digit != 0) {
            is_zero = false;
            break;
        }
    }
    if (is_zero) {
        return std::vector<digit_t> {0};
    }

    /* Convert input digits to an unsigned 64-bit magnitude ---------------- */
    std::uint64_t magnitude {0U};

    for (const digit_t digit : digits) {
        magnitude = (magnitude * static_cast<std::uint64_t>(from_base))
                    + static_cast<std::uint64_t>(digit);
    }

    /* Convert magnitude to the target base -------------------------------- */
    std::vector<digit_t> result_digits;

    while (magnitude > 0U) {
        std::uint64_t remainder {magnitude % static_cast<std::uint64_t>(to_base)};
        result_digits.push_back(static_cast<digit_t>(remainder));
        magnitude = magnitude / static_cast<std::uint64_t>(to_base);
    }

    std::reverse(result_digits.begin(), result_digits.end());

    return result_digits;
}

}  // namespace all_your_base
