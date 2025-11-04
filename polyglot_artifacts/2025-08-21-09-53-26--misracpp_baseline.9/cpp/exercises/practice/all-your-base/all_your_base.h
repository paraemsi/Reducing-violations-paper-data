#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <stdexcept>

namespace all_your_base {

std::vector<unsigned int> convert(int from_base, std::vector<int> const& digits, int to_base);
std::vector<unsigned int> convert(int from_base, std::vector<unsigned int> const& digits, int to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
