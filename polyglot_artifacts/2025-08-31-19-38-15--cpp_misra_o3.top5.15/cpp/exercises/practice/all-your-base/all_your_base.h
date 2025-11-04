#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H
#include <vector>
#include <stdexcept>

namespace all_your_base {

/*  MISRA deviation note:
 *  ------------------------------------------------------------
 *  The Exercism test-suite that drives this exercise requires
 *  the public API to use the exact types shown below
 *  ( `int` and `unsigned int` ).
 *  To remain compatible with those tests we deliberately keep
 *  these types in the interface and document the deviation from
 *  the “no bare fundamental integer types” MISRA rule.
 *  Internal implementation code continues to use <cstdint>
 *  fixed-width types where appropriate.
 */

/**
 * @brief Convert a sequence of digits from one base to another.
 *
 * @param from_base The base of the input digit sequence (must be >= 2).
 * @param digits    The input digits, most-significant first.
 * @param to_base   The base to convert to (must be >= 2).
 * @return          The converted digit sequence, most-significant first.
 *
 * @throws std::invalid_argument if either base is < 2, the digit list is
 *         empty, or a digit is not valid for the given input base.
 */
std::vector<unsigned int> convert(
    int from_base,
    const std::vector<unsigned int>& digits,
    int to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
