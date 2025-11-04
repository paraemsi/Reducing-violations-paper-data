#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H
#include <vector>
#include <cstdint>

namespace all_your_base {

using digit_t = std::uint32_t;
using base_t  = std::int32_t;
using value_t = std::uint64_t;

auto convert(base_t from_base,
             const std::vector<digit_t>& digits,
             base_t to_base) -> std::vector<digit_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
