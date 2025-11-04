#include "all_your_base.h"

#include <algorithm>
#include <cstdint>
#include <cstddef>
#include <stdexcept>
#include <vector>

namespace all_your_base {

std::vector<digit_t> convert(digit_t in_base,
                             const std::vector<digit_t>& digits,
                             digit_t out_base)
{
    if ((in_base < 2U) || (out_base < 2U)) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Validate digit ranges
    for (std::size_t i = static_cast<std::size_t>(0U); i < digits.size(); ++i) {
        if (digits[i] >= in_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    // Trim leading zeros
    std::size_t first_non_zero = static_cast<std::size_t>(0U);
    while ((first_non_zero < digits.size()) && (digits[first_non_zero] == 0U)) {
        ++first_non_zero;
    }

    // If all digits are zero or input is empty, return {0}
    if (first_non_zero == digits.size()) {
        return std::vector<digit_t>(1U, 0U);
    }

    // Initialize the working vector without the leading zeros
    std::vector<digit_t> input;
    input.reserve(digits.size() - first_non_zero);
    for (std::size_t i = first_non_zero; i < digits.size(); ++i) {
        input.push_back(digits[i]);
    }

    std::vector<digit_t> remainders;

    // Repeated division algorithm: divide the input number (in base in_base)
    // by out_base, collecting remainders, until the quotient becomes zero.
    while (!input.empty()) {
        std::uint64_t carry = static_cast<std::uint64_t>(0U);
        std::vector<digit_t> quotient;
        quotient.reserve(input.size());

        bool started = false;

        for (std::size_t i = static_cast<std::size_t>(0U); i < input.size(); ++i) {
            const std::uint64_t acc =
                (carry * static_cast<std::uint64_t>(in_base)) + static_cast<std::uint64_t>(input[i]);

            const digit_t q =
                static_cast<digit_t>(acc / static_cast<std::uint64_t>(out_base));
            const digit_t r =
                static_cast<digit_t>(acc % static_cast<std::uint64_t>(out_base));

            if (started || (q != 0U)) {
                quotient.push_back(q);
                started = true;
            }

            carry = static_cast<std::uint64_t>(r);
        }

        remainders.push_back(static_cast<digit_t>(carry));
        input = quotient;
    }

    // Remainders are collected least-significant first; reverse to get the result.
    std::reverse(remainders.begin(), remainders.end());

    return remainders;
}

}  // namespace all_your_base
