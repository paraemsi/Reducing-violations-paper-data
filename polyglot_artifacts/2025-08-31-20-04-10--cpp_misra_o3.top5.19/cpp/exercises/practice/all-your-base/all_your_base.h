#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t from_base,
                                   const std::vector<std::uint32_t>& digits,
                                   std::uint32_t to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
