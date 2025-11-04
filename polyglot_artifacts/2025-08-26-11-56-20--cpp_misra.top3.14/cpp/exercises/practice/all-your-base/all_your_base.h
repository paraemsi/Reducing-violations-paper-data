#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

using digit_t = std::uint32_t;

std::vector<digit_t> convert(digit_t input_base, const std::vector<digit_t>& digits, digit_t output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
