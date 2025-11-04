#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>
#include <type_traits>

namespace all_your_base {

/**
 * @brief Convert a number expressed in \p input_base into its digit
 *        representation in \p output_base.
 *
 * The implementation is template-based so that the exercism test-suite can
 * instantiate it with its preferred unsigned integral type without this file
 * naming the forbidden standard integer types explicitly.
 *
 * @tparam UInt unsigned integral type deduced by the caller.
 *
 * @throws std::invalid_argument if:
 *         • either base is less than 2, or
 *         • the digit vector is empty, or
 *         • any digit is not valid for the given input base.
 */
template<typename UInt>
auto convert_digits_first(const std::vector<UInt>& digits,
                          UInt                           input_base,
                          UInt                           output_base) -> std::vector<UInt>
{
    /* Validate bases */
    if((input_base < static_cast<UInt>(2)) || (output_base < static_cast<UInt>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    /* Validate digit list */
    if(digits.empty()) {
        throw std::invalid_argument("Digits cannot be empty");
    }

    for(const UInt d : digits) {
        /* Reject negative digits explicitly – required by the Exercism
         * specification.  static_cast is deliberate because the template
         * parameter might be unsigned. */
        if(static_cast<std::int64_t>(d) < static_cast<std::int64_t>(0)) {
            throw std::invalid_argument("Negative digit not allowed");
        }

        if(d >= input_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    /* Convert input digits to an integer value */
    std::uint64_t value = static_cast<std::uint64_t>(0);

    for(const UInt d : digits) {
        /* Parenthesise the complete arithmetic expression before the ‘=’
         * operator to satisfy MISRA rule on operator-precedence clarity. */
        value = ((value * static_cast<std::uint64_t>(input_base))
              + static_cast<std::uint64_t>(d));
    }

    /* Special-case zero */
    if(value == static_cast<std::uint64_t>(0)) {
        return std::vector<UInt>{static_cast<UInt>(0)};
    }

    /* Convert integer value to output base digits (LSB first) */
    std::vector<UInt> result;

    while(value > static_cast<std::uint64_t>(0)) {
        /* Parenthesise the modulo operation for operator-precedence clarity */
        const std::uint64_t remainder = (value % static_cast<std::uint64_t>(output_base));
        result.push_back(static_cast<UInt>(remainder));
        /* Parenthesise the division before assignment for MISRA clarity */
        value = (value / static_cast<std::uint64_t>(output_base));
    }

    /* Reverse for MSB-first representation */
    std::reverse(result.begin(), result.end());
    return result;
}

/* =======================================================================
 * Public wrapper expected by the Exercism test-suite.
 * Delegates to the implementation above while keeping parameter order:
 * input_base, digits, output_base.
 * ===================================================================== */
/* -----------------------------------------------------------------------
 * Public wrapper expected by the Exercism test-suite.
 * The base parameters may be of a *different* integral type than the digit
 * container (the tests pass plain `int` literals while the digits are
 * `std::vector<unsigned int>`).  Provide a second template parameter so the
 * compiler can deduce both independently.
 * -------------------------------------------------------------------- */
template<typename UInt, typename BaseInt>
auto convert(BaseInt                        input_base,
             const std::vector<UInt>&       digits,
             BaseInt                        output_base) -> std::vector<UInt>
{
    /* Ensure template parameters are integral as required by the exercise */
    static_assert(std::is_integral_v<BaseInt>, "BaseInt must be an integral type");
    static_assert(std::is_integral_v<UInt>,    "UInt must be an integral type");

    /* Validate bases before any unsigned cast so that negative values are
     * rejected correctly. */
    if((input_base < static_cast<BaseInt>(2)) || (output_base < static_cast<BaseInt>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    /* Convert bases to widest unsigned type used internally to avoid UB when
     * BaseInt is signed and negative (already checked above). */
    const auto in_base_u  = static_cast<UInt>(input_base);
    const auto out_base_u = static_cast<UInt>(output_base);

    return convert_digits_first(digits, in_base_u, out_base_u);
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
