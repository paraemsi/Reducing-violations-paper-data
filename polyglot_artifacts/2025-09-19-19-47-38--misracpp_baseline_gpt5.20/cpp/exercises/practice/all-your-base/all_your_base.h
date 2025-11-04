#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <stdexcept>

namespace all_your_base {

// Convert a sequence of digits from in_base to out_base.
std::vector<unsigned int> convert(unsigned int in_base,
                                  const std::vector<unsigned int>& in_digits,
                                  unsigned int out_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
