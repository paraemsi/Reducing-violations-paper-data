#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>

namespace all_your_base {

[[nodiscard]] digits_t convert(base_t          from_base,
                 const digits_t& input_digits,
                 base_t          to_base)
{
    /* Validate bases */
    if((from_base < static_cast<base_t>(2)) || (to_base < static_cast<base_t>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    /* Validate digits */
    if(input_digits.empty()) {
        throw std::invalid_argument("Input digit sequence must not be empty");
    }

    std::uint64_t value = 0U;
    for(const base_t digit : input_digits) {
        if(digit >= from_base) {
            throw std::invalid_argument("Digit out of range for the source base");
        }
        value = (value * static_cast<std::uint64_t>(from_base))
              + static_cast<std::uint64_t>(digit);
    }

    /* Special-case zero */
    if(value == 0U) {
        return digits_t{static_cast<base_t>(0)};
    }

    /* Convert to target base */
    digits_t result {};
    while(value > 0U) {
        const base_t remainder = static_cast<base_t>(
            value % static_cast<std::uint64_t>(to_base));
        result.push_back(remainder);
        value = value / static_cast<std::uint64_t>(to_base);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
