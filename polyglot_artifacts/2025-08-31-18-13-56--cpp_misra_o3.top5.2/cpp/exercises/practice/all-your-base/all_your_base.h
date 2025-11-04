#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

using digit_t  = std::uint32_t;
using digits_t = std::vector<digit_t>;

/*
 * Convert a sequence of digits expressed in 'from_base' to an
 * equivalent sequence expressed in 'to_base'.
 * Throws std::invalid_argument on any error (invalid base, digit out of range,
 * or empty input sequence).
 */
digits_t convert(digit_t from_base, const digits_t& digits, digit_t to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
