#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <stdexcept>

namespace all_your_base {

/**
 * Convert a sequence of digits from input_base to output_base.
 * - Throws std::invalid_argument if either base < 2 or a digit is >= input_base.
 * - Returns {0} when the input represents zero (empty or all leading zeros).
 */
std::vector<unsigned int> convert(int input_base,
                                  const std::vector<unsigned int>& in_digits,
                                  int output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
