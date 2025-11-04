#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

 // Convert a number represented as digits in base `in_base` to digits in base `out_base`.
 // - Bases must be >= 2; digits must be < in_base.
 // - Leading zeros are ignored. Zero value yields an empty vector.
std::vector<std::uint32_t> convert(std::uint32_t in_base, const std::vector<std::uint32_t>& digits, std::uint32_t out_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
