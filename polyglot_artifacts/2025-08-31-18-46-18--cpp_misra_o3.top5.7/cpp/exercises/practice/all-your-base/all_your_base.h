#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

using digit_t = std::uint32_t;

/**
 * \brief Convert a sequence of digits from one base to another.
 *
 * \param from_base    The base that \p input_digits are expressed in (≥ 2).
 * \param input_digits The digits of the number expressed in \p from_base.
 *                     The most-significant digit is at index&nbsp;0.
 * \param to_base      The base that the result should be expressed in (≥ 2).
 * \return             The converted digits expressed in \p to_base.
 *
 * \throws std::invalid_argument If the bases are invalid, a digit is out of
 *                               range, or \p input_digits is empty.
 */
auto convert(digit_t                         from_base,
             const std::vector<digit_t>&     input_digits,
             digit_t                         to_base)
    -> std::vector<digit_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
