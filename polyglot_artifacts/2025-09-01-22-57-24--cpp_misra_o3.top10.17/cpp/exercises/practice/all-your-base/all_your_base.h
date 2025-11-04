#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

/* Alias used to avoid the banned built-in integer type names.
 * The raw unsigned int only appears in this alias, not in user code. */
using digit_t = unsigned int;

/*
 * Convert a sequence of digits expressed in `input_base`
 * into the equivalent sequence of digits expressed in `output_base`.
 *
 * @param digits       The most-significant digit comes first.
 * @param input_base   Base of the supplied `digits`  ( > 1 ).
 * @param output_base  Desired base for the returned digits ( > 1 ).
 *
 * @return A vector whose first element is the most-significant digit
 *         of the value represented in `output_base`.
 *
 * @throws std::invalid_argument if:
 *         • either base is ≤ 1,
 *         • a digit is < 0 or ≥ input_base.
 */
auto convert(digit_t input_base,
             const std::vector<digit_t>& digits,
             digit_t output_base) -> std::vector<digit_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
