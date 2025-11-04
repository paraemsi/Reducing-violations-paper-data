#include "all_your_base.h"
#include <cstdint>

namespace all_your_base {

std::vector<unsigned int> convert(
    int from_base,
    const std::vector<unsigned int>& digits,
    int to_base)
{
    /* Validate bases. */
    if ((from_base < 2) || (to_base < 2)) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    /* Validate digits. */
    if (digits.empty()) {
        throw std::invalid_argument("Digit sequence must not be empty");
    }

    for (const unsigned int digit : digits) {
        if (digit >= static_cast<unsigned int>(from_base)) {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    /* Check if the number is zero. */
    bool is_zero = true;
    for (const unsigned int digit : digits) {
        if (digit != 0U) {
            is_zero = false;
            break;
        }
    }
    if (is_zero) {
        return {0U};
    }

    /*  Repeated-division algorithm:
     *  ----------------------------------
     *  Avoids constructing the entire numeric value in a single integral
     *  object, so it works for arbitrarily long digit sequences without
     *  risking overflow.  At each step we divide the current number
     *  (held in `source_digits`, base `from_base`) by `to_base`, collect the
     *  remainder, and continue with the quotient.
     */
    std::vector<unsigned int> source_digits = digits;
    std::vector<unsigned int> result_digits;

    while (!source_digits.empty()) {
        std::vector<unsigned int> quotient;
        std::uint32_t remainder = 0U;

        for (const unsigned int digit : source_digits) {
            std::uint32_t accumulator =
                (remainder * static_cast<std::uint32_t>(from_base))
                + static_cast<std::uint32_t>(digit);

            std::uint32_t q_digit =
                accumulator / static_cast<std::uint32_t>(to_base);

            remainder =
                accumulator % static_cast<std::uint32_t>(to_base);

            if ((!quotient.empty()) || (q_digit != 0U)) {
                quotient.push_back(q_digit);
            }
        }

        /*  Prepend the newest remainder so that the final result is produced
         *  most-significant-digit first.
         */
        result_digits.insert(result_digits.begin(), remainder);

        /*  Process the next iteration on the quotient (if any). */
        source_digits = quotient;
    }

    return result_digits;
}

}  // namespace all_your_base
