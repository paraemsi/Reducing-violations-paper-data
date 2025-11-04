#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

using digit_t  = std::uint32_t;
using digits_t = std::vector<digit_t>;

/*
 * Convert a sequence of digits from one base to another.
 *
 * @param input_digits  Digits of the number in base 'from_base', most-significant first.
 * @param from_base     Source base (>= 2).
 * @param to_base       Target base (>= 2).
 * @return              Digits of the converted number in base 'to_base', most-significant first.
 * @throws std::invalid_argument if any base is < 2, digit is out of range, or input invalid.
 */
auto convert(std::uint32_t   from_base,
             const digits_t& input_digits,
             std::uint32_t   to_base) -> digits_t;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
