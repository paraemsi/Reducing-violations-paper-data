#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

// Define aliases to match the test interface while using fixed-width types internally
using base_t = std::uint32_t;
using digit_t = std::uint32_t;

std::vector<std::uint8_t> convert(unsigned int input_base, 
                                  const std::vector<unsigned int>& input_digits,
                                  unsigned int output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
