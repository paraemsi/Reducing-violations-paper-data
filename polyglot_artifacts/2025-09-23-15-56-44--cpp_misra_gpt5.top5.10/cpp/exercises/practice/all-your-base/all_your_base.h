#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

// Convert digits from in_base to out_base.
// - Bases must be >= 2, otherwise std::invalid_argument is thrown.
// - Any digit >= in_base results in std::invalid_argument.
// - Leading zeros are permitted; if the value is zero or the input is empty,
//   the result is an empty digit list.
// Notes on types (MISRA):
// - Fixed-width integer types are used.
// - The result uses std::uint32_t digits.
auto convert(std::uint32_t in_base,
             const std::vector<std::uint32_t>& digits,
             std::uint32_t out_base) -> std::vector<std::uint32_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
