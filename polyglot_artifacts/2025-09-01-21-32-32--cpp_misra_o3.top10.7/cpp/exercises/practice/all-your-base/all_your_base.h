#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>
#include <type_traits>

namespace all_your_base {

    auto convert(std::uint32_t from_base,
                 const std::vector<std::uint32_t>& digits,
                 std::uint32_t to_base) -> std::vector<std::uint32_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
