#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

typedef std::uint32_t digit_t;

std::vector<digit_t> convert(digit_t input_base, std::vector<digit_t> const& digits, digit_t output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
