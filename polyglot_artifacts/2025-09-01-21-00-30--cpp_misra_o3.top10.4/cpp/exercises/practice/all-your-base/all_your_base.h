#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace all_your_base {

using digit_t = std::uint32_t;
using base_t  = std::uint32_t;

/**
 * @brief Convert a sequence of digits in one base to another base.
 *
 * @param from_base    Source base (>= 2).
 * @param input_digits Digits in @p from_base, most-significant digit first.
 * @param to_base      Destination base (>= 2).
 *
 * @return Digits of the same value in @p to_base, most-significant digit first.
 *
 * @throw std::invalid_argument If a base is < 2 or a digit is invalid.
 */
auto convert(base_t from_base,
             const std::vector<digit_t>& input_digits,
             base_t to_base) -> std::vector<digit_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
