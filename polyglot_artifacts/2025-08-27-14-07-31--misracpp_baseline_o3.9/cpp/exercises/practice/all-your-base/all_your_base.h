#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <stdexcept>

namespace all_your_base {

// Convert the sequence of `digits` expressed in `from_base`
// into a new sequence expressed in `to_base`.
//
// Preconditions:
//   * from_base > 1
//   * to_base   > 1
//   * digits is non-empty and contains no leading minus signs
//   * each digit 0 <= d < from_base
//
// Throws std::invalid_argument if any precondition is violated.
std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
