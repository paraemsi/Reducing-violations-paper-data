#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

digits_t convert(digit_t from_base, const digits_t& digits, digit_t to_base)
{
    /* Validate bases */
    if((from_base < static_cast<digit_t>(2U)) || (to_base < static_cast<digit_t>(2U))) {
        throw std::invalid_argument("Base must be >= 2");
    }

    /* Validate digit sequence */
    if(digits.empty()) {
        throw std::invalid_argument("Digit sequence is empty");
    }

    for(const digit_t value : digits) {
        if(value >= from_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    /* Remove any leading zeros from the input sequence */
    digits_t working_digits{};
    {
        auto first_non_zero_it =
            std::find_if(digits.begin(), digits.end(),
                         [](digit_t v) noexcept { return v != static_cast<digit_t>(0U); });
        if(first_non_zero_it == digits.end()) {
            return digits_t{static_cast<digit_t>(0U)};
        }
        working_digits.assign(first_non_zero_it, digits.end());
    }

    digits_t result{};

    /* Convert by repeated division, thereby avoiding construction of a
     * potentially overflowing large intermediate integer. */
    while(!working_digits.empty()) {

        digits_t next_working{};
        std::uint64_t carry = 0U;

        for(const digit_t value : working_digits) {
            const std::uint64_t accumulator =
                ((carry * static_cast<std::uint64_t>(from_base))
                 + static_cast<std::uint64_t>(value));

            const digit_t quotient_digit =
                static_cast<digit_t>(accumulator / static_cast<std::uint64_t>(to_base));
            carry = (accumulator % static_cast<std::uint64_t>(to_base));

            if((!next_working.empty()) || (quotient_digit != static_cast<digit_t>(0U))) {
                next_working.push_back(quotient_digit);
            }
        }

        /* 'carry' now holds the remainder for this iteration (next least-significant digit) */
        result.push_back(static_cast<digit_t>(carry));

        working_digits.swap(next_working);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
