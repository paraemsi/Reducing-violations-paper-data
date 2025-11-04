#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

using digit_t = unsigned int;   /* alias hides raw type per MISRA */

/*
 * Convert a sequence of digits expressed in a given source base to the
 * corresponding sequence of digits in a target base.
 *
 * \param digits     The input digits, most–significant digit first.
 * \param from_base  The base the input digits are expressed in  (≥ 2).
 * \param to_base    The base to convert the number to            (≥ 2).
 *
 * \return A vector containing the converted digits,
 *         most–significant digit first.
 *
 * \throws std::invalid_argument if:
 *         – either base is less than 2,
 *         – the digit sequence is empty,
 *         – any digit is not valid for the source base.
 */
auto convert(digit_t                     from_base,
             const std::vector<digit_t>& digits,
             digit_t                     to_base) -> std::vector<digit_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
