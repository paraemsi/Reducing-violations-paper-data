#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

/*
 * Convert a non-negative number represented by `digits` in `from_base`
 * into a vector of digits in `to_base`.
 *
 * Preconditions:
 * - `from_base` >= 2
 * - `to_base`   >= 2
 * - `digits` is non-empty and every element is < `from_base`
 *
 * Throws std::invalid_argument on any pre-condition violation.
 */
[[nodiscard]] auto convert(std::uint32_t from_base,
             const std::vector<std::uint32_t>& digits,
             std::uint32_t to_base) -> std::vector<std::uint32_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
