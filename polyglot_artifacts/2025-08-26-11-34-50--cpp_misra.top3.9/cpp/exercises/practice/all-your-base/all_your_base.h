#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

typedef std::uint32_t base_digit_t;

std::vector<base_digit_t> convert(base_digit_t input_base, const std::vector<base_digit_t>& digits, base_digit_t output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
