#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>

namespace all_your_base {

// Overload 1: input_base first
std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int output_base);

// Overload 2: digits first
std::vector<unsigned int> convert(const std::vector<unsigned int>& digits,
                                  unsigned int input_base,
                                  unsigned int output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
