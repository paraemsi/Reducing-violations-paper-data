#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>
#include <stdexcept>

namespace all_your_base {

using digit_t = std::uint32_t;
using digits_t = std::vector<digit_t>;

// Convert digits from in_base to out_base.
// Rules:
// - in_base and out_base must be >= 2; otherwise std::invalid_argument is thrown.
// - All digits must be < in_base; otherwise std::invalid_argument is thrown.
// - Leading zeros are allowed; empty input or all-zero input yields {0}.
auto convert(std::uint32_t in_base, digits_t const& in_digits, std::uint32_t out_base) -> digits_t;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
