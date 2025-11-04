#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

using digit_t = std::uint32_t;
using digits_t = std::vector<digit_t>;

// MISRA-preferred fixed-width API
digits_t convert(digit_t in_base, const digits_t& in_digits, digit_t out_base);
digits_t convert(const digits_t& in_digits, digit_t in_base, digit_t out_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
