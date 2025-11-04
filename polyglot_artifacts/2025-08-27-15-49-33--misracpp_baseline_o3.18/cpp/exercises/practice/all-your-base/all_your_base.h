#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <stdexcept>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& in_digits,
                                  unsigned int to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
