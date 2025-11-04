#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

/*
 * Convert a sequence of digits expressed in `input_base`
 * into an equivalent sequence expressed in `output_base`.
 *
 * Preconditions:
 * - `input_base`  > 1U
 * - `output_base` > 1U
 * - every element of `input_digits` is < `input_base`
 *
 * Throws:
 * - std::invalid_argument if any pre-condition is violated
 */
auto convert(std::uint32_t input_base,
             const std::vector<std::uint32_t>& input_digits,
             std::uint32_t output_base) -> std::vector<std::uint32_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
