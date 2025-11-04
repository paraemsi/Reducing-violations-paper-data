#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

using digit_t = unsigned int;

std::vector<digit_t> convert(digit_t in_base,
                             const std::vector<digit_t>& digits,
                             digit_t out_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
