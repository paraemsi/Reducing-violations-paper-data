#include "all_your_base.h"
#include <stdexcept>
#include <algorithm>
#include <cstdint>

namespace all_your_base {

auto convert(base_t from_base,
             const std::vector<digit_t>& digits,
             base_t to_base) -> std::vector<digit_t>
{
    if ((from_base < static_cast<base_t>(2)) || (to_base < static_cast<base_t>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if (digits.empty() == true) {
        throw std::invalid_argument("Input digits may not be empty");
    }

    value_t value = static_cast<value_t>(0U);

    for (const digit_t digit : digits) {
        if (digit >= static_cast<digit_t>(from_base)) {
            throw std::invalid_argument("Digit out of range for input base");
        }

        value = (value * static_cast<value_t>(from_base))
                + static_cast<value_t>(digit);
    }

    if (value == static_cast<value_t>(0U)) {
        return { static_cast<digit_t>(0) };
    }

    std::vector<digit_t> output_digits {};

    while (value > static_cast<value_t>(0U)) {
        const value_t remainder = value % static_cast<value_t>(to_base);
        output_digits.push_back(static_cast<digit_t>(remainder));
        value = value / static_cast<value_t>(to_base);
    }

    std::reverse(output_digits.begin(), output_digits.end());
    return output_digits;
}

}  // namespace all_your_base
