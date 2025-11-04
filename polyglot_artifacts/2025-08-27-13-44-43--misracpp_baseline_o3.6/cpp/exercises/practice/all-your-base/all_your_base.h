#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>

namespace all_your_base {

/**
 * Convert a sequence of digits that represents a number in `from_base`
 * into a sequence of digits representing the same value in `to_base`.
 *
 * @param from_base  Base of the input number ( ≥ 2 ).
 * @param digits     Most-significant digit first. May contain a single 0.
 * @param to_base    Desired base of the output number ( ≥ 2 ).
 *
 * @throws std::invalid_argument if:
 *   * `from_base` or `to_base` is < 2
 *   * `digits` is empty
 *   * `digits` contains a value ≥ `from_base`
 *   * `digits` has leading zeros (size() > 1 and digits[0] == 0)
 *
 * @returns A vector with the digits of the converted number, most-significant
 *          digit first. Zero is returned as {0}.
 */
std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
