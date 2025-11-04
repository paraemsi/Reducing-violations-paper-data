#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <stdexcept>

namespace all_your_base {

// Convert `digits` interpreted in `from_base` to their representation in `to_base`.
// Throws std::invalid_argument if bases are < 2 or if `digits` contains invalid values.
std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
