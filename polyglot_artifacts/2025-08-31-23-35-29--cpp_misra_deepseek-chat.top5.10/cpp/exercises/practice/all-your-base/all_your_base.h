#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

// Create aliases that are fixed-width types
using u32 = std::uint32_t;

std::vector<u32> convert(u32 input_base,
                         const std::vector<u32>& digits,
                         u32 output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
