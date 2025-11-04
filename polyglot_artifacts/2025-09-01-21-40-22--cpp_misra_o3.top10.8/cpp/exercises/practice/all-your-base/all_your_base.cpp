#include "all_your_base.h"

#include <algorithm>    /* for std::reverse */

namespace all_your_base {

auto convert(digit_t                        from_base,
             const std::vector<digit_t>&    in_digits,
             digit_t                        to_base)
             -> std::vector<digit_t>
{
    /* Validate bases */
    if ((from_base < static_cast<digit_t>(2U)) || (to_base < static_cast<digit_t>(2U))) {
        throw std::invalid_argument("Base must be ≥ 2");
    }

    /* Validate digit sequence */
    if (in_digits.empty()) {
        throw std::invalid_argument("Input digit sequence must not be empty");
    }

    for (const digit_t digit : in_digits) {
        if (digit >= from_base) {
            throw std::invalid_argument("Digit outside input base");
        }
    }

    /* Remove leading zeros, if present */
    auto first_non_zero_it = std::find_if(
        in_digits.begin(),
        in_digits.end(),
        [](digit_t d) { return d != static_cast<digit_t>(0U); });

    if (first_non_zero_it == in_digits.end()) {
        /* The number represented is zero */
        return std::vector<digit_t>{ static_cast<digit_t>(0U) };
    }

    /* Work on a copy that omits leading zeros */
    std::vector<digit_t> input_digits{ first_non_zero_it, in_digits.end() };
    std::vector<digit_t> output_digits{};

    /* Repeated-division algorithm: keeps arithmetic in-range, no global overflow */
    while (!input_digits.empty()) {
        std::vector<digit_t> next_digits{};
        std::uint64_t        carry{ 0U };

        for (const digit_t digit : input_digits) {
            const std::uint64_t accumulator{
                (carry * static_cast<std::uint64_t>(from_base))
                + static_cast<std::uint64_t>(digit)
            };

            const digit_t quotient_digit{
                static_cast<digit_t>(accumulator / static_cast<std::uint64_t>(to_base))
            };
            carry = accumulator % static_cast<std::uint64_t>(to_base);

            if ((!next_digits.empty()) || (quotient_digit != static_cast<digit_t>(0U))) {
                next_digits.push_back(quotient_digit);
            }
        }

        /* Remainder of the division gives the next least-significant digit */
        output_digits.push_back(static_cast<digit_t>(carry));

        /* Continue with the quotient for the next iteration */
        input_digits.swap(next_digits);
    }

    /* Result produced LSB → MSB; reverse to MSB → LSB */
    std::reverse(output_digits.begin(), output_digits.end());

    return output_digits;
}

}  // namespace all_your_base
