#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

auto convert(int_t input_base,
             const std::vector<int_t>& digits,
             int_t output_base) -> std::vector<int_t>
{
    if ((input_base < 2) || (output_base < 2)) {
        throw std::invalid_argument("bases must be >= 2");
    }

    if (digits.empty()) {
        throw std::invalid_argument("digit sequence may not be empty");
    }

    /* Convert the incoming digits to a fixed-width type for safe arithmetic. */
    std::vector<int_t> internal_digits;
    internal_digits.reserve(digits.size());
    for (const int_t d : digits) {
        internal_digits.push_back(d);
    }

    std::uint64_t value = 0U;

    for (const int_t digit : internal_digits) {
        if (digit >= static_cast<int_t>(input_base)) {
            throw std::invalid_argument("invalid digit for input base");
        }

        value = ((value * static_cast<std::uint64_t>(input_base)) +
                 static_cast<std::uint64_t>(digit));
    }

    if (value == 0U) {
        return std::vector<int_t>{0U};
    }

    std::vector<int_t> result;

    while (value > 0U) {
        result.push_back(static_cast<int_t>(
            value % static_cast<std::uint64_t>(output_base)));
        value = value / static_cast<std::uint64_t>(output_base);
    }

    std::reverse(result.begin(), result.end());

    return result;
}

}  // namespace all_your_base
