#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H
#include <vector>
#include <cstdint>

namespace all_your_base {

using base_t   = std::uint32_t;
using digits_t = std::vector<base_t>;

/*
 * Convert a sequence of digits expressed in `from_base`
 * into a sequence of digits expressed in `to_base`.
 *
 * Preconditions:
 *  • `from_base` and `to_base` are ≥ 2
 *  • `input_digits` is non-empty, each digit is 0 ≤ d < from_base
 *
 * Throws std::invalid_argument on any pre-condition violation.
 */
[[nodiscard]] digits_t convert(base_t          from_base,
                 const digits_t& input_digits,
                 base_t          to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
