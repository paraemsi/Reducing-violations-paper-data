#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

// Type aliases chosen for external API compatibility with exercise tests.
using digit_t = unsigned int;
using base_t = unsigned int;

// Convert digits from in_base to out_base.
// Returns an empty vector on any invalid input (base < 2, invalid digit, empty input).
std::vector<digit_t> convert(base_t in_base, const std::vector<digit_t>& digits, base_t out_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
