#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>

namespace all_your_base {

// Convert a sequence of digits in input_base to a sequence of digits in output_base.
// Throws std::invalid_argument on invalid bases (< 2) or invalid digits (>= input_base).
std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
