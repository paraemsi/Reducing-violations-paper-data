#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>

namespace all_your_base {

using wide_digit_t = std::uint64_t;

auto convert(digit_t                         from_base,
             const std::vector<digit_t>&     input_digits,
             digit_t                         to_base)
    -> std::vector<digit_t>
{
    /* Validate bases */
    if ((from_base < static_cast<digit_t>(2U)) || (to_base < static_cast<digit_t>(2U))) {
        throw std::invalid_argument("Bases must be at least 2");
    }

    /* Validate input */
    if (input_digits.empty()) {
        throw std::invalid_argument("No digits supplied");
    }

    /* Strip leading zeros yet keep at least one digit */
    auto first_non_zero = std::find_if(
        input_digits.begin(),
        input_digits.end(),
        [](digit_t d) noexcept { return d != static_cast<digit_t>(0U); });

    if (first_non_zero == input_digits.end()) {
        /* The value is zero */
        return std::vector<digit_t>{static_cast<digit_t>(0U)};
    }

    /* Convert to an intermediate value using 64-bit accumulator */
    wide_digit_t value = static_cast<wide_digit_t>(0U);
    for (auto it = first_non_zero; it != input_digits.end(); ++it) {
        const digit_t digit = *it;
        if (digit >= from_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
        value = (value * static_cast<wide_digit_t>(from_base))
                + static_cast<wide_digit_t>(digit);
    }

    /* Convert from intermediate value to the target base */
    std::vector<digit_t> result{};
    while (value > static_cast<wide_digit_t>(0U)) {
        const digit_t remainder = static_cast<digit_t>(
            value % static_cast<wide_digit_t>(to_base));
        result.push_back(remainder);
        value = value / static_cast<wide_digit_t>(to_base);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
