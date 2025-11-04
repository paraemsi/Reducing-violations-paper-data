#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

using digit_t = unsigned int;  // Alias permitted: basic type used only inside alias per MISRA

/*
 * Convert a sequence of digits expressed in the positional numeral system
 * defined by `input_base` into the sequence of digits expressed in
 * `output_base`.  The function validates all pre-conditions and will
 * throw `std::invalid_argument` when the conversion request is not
 * well-formed according to the Exercism specification.
 */
auto convert(digit_t input_base,
             const std::vector<digit_t>& digits,
             digit_t output_base) -> std::vector<digit_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
