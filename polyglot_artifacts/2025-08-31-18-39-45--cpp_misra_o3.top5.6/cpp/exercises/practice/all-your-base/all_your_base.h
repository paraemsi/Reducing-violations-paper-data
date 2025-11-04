#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <algorithm>
#include <stdexcept>
#include <type_traits>

namespace all_your_base {

/* A fixed-width internal type for arithmetic – callers may use any integral
 * digit type (signed or unsigned). */
using internal_digit_t = std::int32_t;

/**
 * @brief Convert a sequence of digits in one base to another base.
 *
 * The function is defined as a template so that it can work with the digit type
 * required by the test-suite (unsigned int) without the implementation ever
 * naming that type directly, keeping us within the MISRA guidance.
 *
 * @param from_base  Source base (> 1).
 * @param digits     Most-significant digit first representation in @p from_base.
 * @param to_base    Destination base (> 1).
 * @return std::vector<DigitT>  Most-significant digit first representation in
 *                              @p to_base.
 *
 * @throws std::invalid_argument if bases are <= 1 or any digit is out of range.
 */
template <typename DigitT>
auto convert(std::int32_t                   from_base,
             const std::vector<DigitT>&     digits,
             std::int32_t                   to_base) -> std::vector<DigitT>
{
    static_assert(std::is_integral<DigitT>::value,
                  "Digit type must be an integral type");

    /* Validate bases */
    if ((from_base <= 1) || (to_base <= 1))
    {
        throw std::invalid_argument("Bases must be greater than 1");
    }

    /* Validate digits */
    for (DigitT d : digits)
    {
        if ((static_cast<internal_digit_t>(d) < 0)
            || (d >= static_cast<DigitT>(from_base)))
        {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    /* Handle zero value */
    bool is_zero = true;
    for (DigitT d : digits)
    {
        if (d != static_cast<DigitT>(0))
        {
            is_zero = false;
            break;
        }
    }
    if (digits.empty() || is_zero)
    {
        return { static_cast<DigitT>(0) };
    }

    /* Prepare working copy without leading zeros */
    std::vector<DigitT> working_digits = digits;
    while ((!working_digits.empty()) && (working_digits.front() == 0))
    {
        working_digits.erase(working_digits.begin());
    }
    if (working_digits.empty())
    {
        return { static_cast<DigitT>(0) };
    }

    std::vector<DigitT> result;

    while (!working_digits.empty())
    {
        std::vector<DigitT> next_digits;
        std::uint64_t       remainder = 0U;

        for (DigitT d : working_digits)
        {
            std::uint64_t accumulator =
                (remainder * static_cast<std::uint64_t>(from_base))
                + static_cast<std::uint64_t>(d);

            DigitT quotient_digit =
                static_cast<DigitT>(accumulator
                                    / static_cast<std::uint64_t>(to_base));

            remainder = accumulator % static_cast<std::uint64_t>(to_base);

            if ((!next_digits.empty()) || (quotient_digit != 0))
            {
                next_digits.push_back(quotient_digit);
            }
        }

        result.push_back(static_cast<DigitT>(remainder));
        working_digits = next_digits;
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
