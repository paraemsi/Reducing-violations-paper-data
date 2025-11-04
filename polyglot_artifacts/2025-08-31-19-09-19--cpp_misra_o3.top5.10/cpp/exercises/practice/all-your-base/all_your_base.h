#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H
#include <vector>
#include <cstdint>

namespace all_your_base {

using digit_t = std::uint32_t;

/*
 * Convert a sequence of digits expressed in ‘input_base’ into the
 * corresponding sequence of digits expressed in ‘output_base’.
 *
 * Preconditions:
 *   - input_base  >= 2
 *   - output_base >= 2
 *   - Each digit is less than input_base
 *
 * Throws std::invalid_argument if any precondition is violated.
 */
auto convert(std::uint32_t input_base,
             const std::vector<digit_t>& input_digits,
             std::uint32_t output_base) -> std::vector<digit_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
