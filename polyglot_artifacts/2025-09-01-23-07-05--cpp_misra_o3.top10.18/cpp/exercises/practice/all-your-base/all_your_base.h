#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

/*  Alias for internal computations (unsigned, fixed-width integral type). */
using int_t = std::uint32_t;

auto convert(int_t input_base,
             const std::vector<int_t>& digits,
             int_t output_base) -> std::vector<int_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
