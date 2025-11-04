#include "all_your_base.h"
#include <algorithm>

namespace all_your_base {

auto convert(base_t from_base,
             const std::vector<digit_t>& input_digits,
             base_t to_base) -> std::vector<digit_t>
{
    /* Validate bases */
    if (from_base < static_cast<base_t>(2U)) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (to_base < static_cast<base_t>(2U)) {
        throw std::invalid_argument("output base must be >= 2");
    }

    /* Special-case empty input as zero */
    if (input_digits.empty()) {
        return { static_cast<digit_t>(0) };
    }

    /* Validate digits and detect all-zero input */
    bool is_zero { true };
    for (const digit_t digit : input_digits) {
        if (digit >= static_cast<digit_t>(from_base)) {
            throw std::invalid_argument("digit out of range for input base");
        }
        if (digit != static_cast<digit_t>(0)) {
            is_zero = false;
        }
    }

    if (is_zero != false) {
        return { static_cast<digit_t>(0) };
    }

    /* Convert input digits to an intermediate unsigned 64-bit value */
    std::uint64_t value { 0U };
    for (const digit_t digit : input_digits) {
        /*  Safe – the intermediate value is promoted to 64 bit to avoid overflow,
         *  the final cast back to digit_t is checked to fit within the
         *  destination base range further below. */
        value = ((value * static_cast<std::uint64_t>(from_base)) +
                 static_cast<std::uint64_t>(digit));
    }

    /* Convert the intermediate value to the target base */
    std::vector<digit_t> result_rev {};
    while (value > static_cast<std::uint64_t>(0U)) {
        const std::uint64_t remainder {
            value % static_cast<std::uint64_t>(to_base)
        };
        /*  Deliberate narrowing: 0 ≤ remainder < to_base ≤ UINT32_MAX  */
        result_rev.push_back(static_cast<digit_t>(remainder));
        value = value / static_cast<std::uint64_t>(to_base);
    }

    /* Reverse to produce most-significant digit first */
    std::reverse(result_rev.begin(), result_rev.end());
    return result_rev;
}

}  // namespace all_your_base
