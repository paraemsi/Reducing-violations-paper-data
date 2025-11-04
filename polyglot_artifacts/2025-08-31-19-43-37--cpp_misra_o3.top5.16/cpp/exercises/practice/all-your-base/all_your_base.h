#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

/*
 * Convert a number represented by `digits` in `from_base`
 * into its representation in `to_base`.
 * Returns an empty vector on any input error.
 */

/*  Alias for external unsigned-width type required by the test suite.
 *  Raw fundamental type appears only inside this alias, satisfying MISRA. */
using digit_io_t = unsigned int;

auto convert(digit_io_t from_base,
             const std::vector<digit_io_t>& digits,
             digit_io_t to_base) -> std::vector<digit_io_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
