#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

 // Primary overload: (digits, input_base, output_base)
auto convert(const std::vector<std::uint32_t>& digits,
             std::uint32_t input_base,
             std::uint32_t output_base) -> std::vector<std::uint32_t>;

// Convenience overload: (input_base, digits, output_base)
auto convert(std::uint32_t input_base,
             const std::vector<std::uint32_t>& digits,
             std::uint32_t output_base) -> std::vector<std::uint32_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
