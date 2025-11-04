#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>

namespace all_your_base {

// Convert a sequence of digits `digits`, expressed in `input_base`,
// to an equivalent sequence expressed in `output_base`.
// Both bases must be >= 2 and every digit must be < input_base.
//
// Example (binary 101010 → decimal):
//   convert(2, {1,0,1,0,1,0}, 10) -> {4,2}
//
// Throws std::invalid_argument on invalid bases or digits.
std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
