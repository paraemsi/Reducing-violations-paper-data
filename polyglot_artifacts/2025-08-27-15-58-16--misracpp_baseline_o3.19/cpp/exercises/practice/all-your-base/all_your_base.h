#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>

namespace all_your_base {

/**
 * Convert a number, represented by `digits` in base `from_base`,
 * into a vector of digits in base `to_base`.
 *
 * Preconditions:
 *   - `from_base` and `to_base` must be > 1
 *   - Every element in `digits` must be < `from_base`
 * Throws:
 *   - std::invalid_argument if preconditions are violated
 */
std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
