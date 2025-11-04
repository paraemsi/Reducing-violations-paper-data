#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

typedef std::uint32_t Digit;
typedef std::vector<Digit> Digits;

// Convert a sequence of digits from input_base to output_base.
// Throws std::invalid_argument if input_base or output_base is invalid, or if digits are invalid.
Digits convert(std::uint32_t input_base, const Digits& input_digits, std::uint32_t output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
