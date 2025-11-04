#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

using digit_t = std::uint32_t;
using base_t  = std::int32_t;


/**
 * @brief Convert a number represented as a sequence of digits in one base
 *        to its representation in another base.
 *
 * @param from_base  Base of the incoming representation (≥ 2)
 * @param digits     Most-significant digit first, every element 0 ≤ d < from_base
 * @param to_base    Base of the outgoing representation (≥ 2)
 * @return           Digits of the converted number, most-significant digit first
 *
 * @throws std::invalid_argument if any pre-condition is violated
 */
auto convert(base_t                       from_base,
             const std::vector<digit_t>&  digits,
             base_t                       to_base) -> std::vector<digit_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
