#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <stdexcept>

namespace all_your_base {

// Convert `digits`, expressed in base `from_base`, to its representation in
// base `to_base`.
//
// Preconditions:
//   - `from_base` and `to_base` are at least 2
//   - `digits` is non-empty
//   - every element of `digits` is < `from_base`
//
// Post-conditions:
//   - returns a vector containing the digits (most–significant first)
//     of the converted number in `to_base`
//   - if the value represented by `digits` is zero, returns {0}
std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int> &digits,
                                  unsigned int to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
