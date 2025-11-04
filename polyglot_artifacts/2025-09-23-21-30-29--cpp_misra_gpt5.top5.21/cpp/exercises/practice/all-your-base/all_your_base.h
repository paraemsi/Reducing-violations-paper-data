#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

using digit_t = unsigned int;

std::vector<digit_t> convert(std::uint32_t from_base,
                             const std::vector<digit_t>& digits,
                             std::uint32_t to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
