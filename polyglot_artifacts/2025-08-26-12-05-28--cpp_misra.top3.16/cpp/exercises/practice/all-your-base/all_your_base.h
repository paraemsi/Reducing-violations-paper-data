#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

typedef std::uint32_t base_digit_t;
typedef std::vector<base_digit_t> base_digits_t;

// Convert a sequence of digits in input_base to output_base.
// Throws std::invalid_argument if input is invalid.
base_digits_t convert(base_digit_t input_base, const base_digits_t& input_digits, base_digit_t output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
