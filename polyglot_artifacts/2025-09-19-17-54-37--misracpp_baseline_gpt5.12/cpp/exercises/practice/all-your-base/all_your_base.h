#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <stdexcept>

namespace all_your_base {

// Convert a sequence of digits in input_base to a sequence of digits in output_base.
// - digits may contain leading zeros, which are ignored.
// - Throws std::invalid_argument if input_base < 2, output_base < 2, or any digit is invalid.
// - Returns {0} if the value of digits is zero.
std::vector<unsigned int> convert(const std::vector<unsigned int>& digits,
                                  int input_base,
                                  int output_base);


}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
