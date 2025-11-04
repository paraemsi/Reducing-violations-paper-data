#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

using integer = std::uint32_t;
using sequence = std::vector<integer>;

sequence convert(const integer input_base,
                 const sequence& digits,
                 const integer output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
