#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

using Base = std::uint32_t;
using Digit = std::uint32_t;

std::vector<Digit> convert(Base in_base,
                           const std::vector<Digit>& digits,
                           Base out_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
