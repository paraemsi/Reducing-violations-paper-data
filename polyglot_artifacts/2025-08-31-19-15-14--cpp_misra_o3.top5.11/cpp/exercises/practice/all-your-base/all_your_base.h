#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

 // Fixed-width unsigned integer type used for digits
 // NOLINTNEXTLINE(misra-cpp2008-2-2-1) - tests require unsigned int digits
using digit_t  = unsigned int;
using digits_t = std::vector<digit_t>;

/*
 * Convert a number represented by the sequence `input_digits`
 * from `input_base` to `output_base`.
 *
 * Preconditions
 *  • input_base  > 1
 *  • output_base > 1
 *  • Every digit 0 ≤ d < input_base
 *  • No leading zero unless the number itself is zero
 *
 * Throws std::invalid_argument if any pre-condition is violated.
 */
auto convert(std::int32_t     input_base,
             const digits_t&  input_digits,
             std::int32_t     output_base) -> digits_t;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
