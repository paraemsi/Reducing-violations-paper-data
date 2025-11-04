#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

using digit_type = unsigned int;
using base_type = unsigned int;

// Convert a sequence of digits from in_base to out_base.
// - digits are most-significant first
// - returns most-significant first
// - throws std::invalid_argument on invalid base (< 2) or digit >= in_base
auto convert(base_type in_base, const std::vector<digit_type>& digits, base_type out_base) -> std::vector<digit_type>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
