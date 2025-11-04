#include "all_your_base.h"

#include <algorithm>
#include <cstdint>
#include <limits>
#include <stdexcept>
#include <vector>

namespace all_your_base {

auto convert(digit_t in_base, const digits_t& in_digits, digit_t out_base) -> digits_t
{
    // Validate bases
    if ((in_base < static_cast<digit_t>(2U)) || (out_base < static_cast<digit_t>(2U))) {
        throw std::invalid_argument("bases must be >= 2");
    }

    // Validate digits and trim leading zeros
    digits_t digits{};
    digits.reserve(in_digits.size());
    bool leading{true};
    for (const digit_t d : in_digits) {
        if (d >= in_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
        if (leading) {
            if (d == static_cast<digit_t>(0U)) {
                // skip leading zeros
            } else {
                leading = false;
                digits.push_back(d);
            }
        } else {
            digits.push_back(d);
        }
    }

    // If all digits were zeros or input empty, the value is zero
    if (digits.empty()) {
        return digits_t{};
    }

    // Repeated division algorithm: divide by out_base, collect remainders
    digits_t output_reversed{};
    output_reversed.reserve(digits.size());

    digits_t current = digits;
    while (!current.empty()) {
        digits_t quotient{};
        quotient.reserve(current.size());
        std::uint32_t remainder{static_cast<std::uint32_t>(0U)};

        for (const digit_t d : current) {
            // acc = remainder * in_base + d; performed in wider type to avoid overflow
            const std::uint64_t acc = (static_cast<std::uint64_t>(remainder) * static_cast<std::uint64_t>(in_base))
                                    + static_cast<std::uint64_t>(d);
            const std::uint32_t q = static_cast<std::uint32_t>(acc / static_cast<std::uint64_t>(out_base));
            remainder = static_cast<std::uint32_t>(acc % static_cast<std::uint64_t>(out_base));

            if ((!quotient.empty()) || (q != static_cast<std::uint32_t>(0U))) {
                quotient.push_back(static_cast<digit_t>(q));
            } else {
                // skip leading zeros in quotient
            }
        }

        output_reversed.push_back(static_cast<digit_t>(remainder));
        current = quotient;
    }

    // Reverse to get most-significant digit first
    std::reverse(output_reversed.begin(), output_reversed.end());
    return output_reversed;
}

auto convert(const digits_t& in_digits, digit_t in_base, digit_t out_base) -> digits_t
{
    return convert(in_base, in_digits, out_base);
}

}  // namespace all_your_base
