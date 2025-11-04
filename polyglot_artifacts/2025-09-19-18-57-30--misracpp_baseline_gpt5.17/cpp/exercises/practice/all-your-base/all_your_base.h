#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>

namespace all_your_base {

// Convert a sequence of digits from input_base to output_base.
// Throws std::invalid_argument for invalid bases (< 2) or digits out of range.
std::vector<unsigned int> convert(const std::vector<unsigned int>& digits,
                                  int input_base,
                                  int output_base);

// Overload to support alternate argument ordering sometimes used in tests.
std::vector<unsigned int> convert(int input_base,
                                  const std::vector<unsigned int>& digits,
                                  int output_base);


}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
