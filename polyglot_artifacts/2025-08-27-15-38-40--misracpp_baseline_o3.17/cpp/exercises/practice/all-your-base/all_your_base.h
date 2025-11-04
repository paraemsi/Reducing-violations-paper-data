#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <stdexcept>

namespace all_your_base {

/**
 * Convert a sequence of digits expressed in `from_base`
 * into a sequence of digits expressed in `to_base`.
 *
 * Preconditions:
 *  - `from_base` and `to_base` are >= 2
 *  - `digits` is non-empty
 *  - Every element in `digits` 0 <= d < from_base
 *
 * Throws std::invalid_argument if any precondition is violated.
 */
std::vector<unsigned int> convert(int from_base,
                                  const std::vector<unsigned int>& digits,
                                  int to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
