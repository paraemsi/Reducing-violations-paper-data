#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <stdexcept>

namespace all_your_base {

/* Convert a sequence of digits from one base to another.
 * Throws std::invalid_argument if bases are invalid (< 2) or digits are out of range.
 */
std::vector<unsigned int> convert(int from_base, const std::vector<unsigned int>& digits, int to_base);
std::vector<unsigned int> convert(const std::vector<unsigned int>& digits, int from_base, int to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
