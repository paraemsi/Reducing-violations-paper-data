#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

/*
 * NOTE: The test suite expects digits to be represented as std::vector<unsigned int>.
 * While our internal guidelines prefer fixed-width integer types, we keep this public
 * alias to maintain API compatibility with the provided tests. All internal arithmetic
 * uses fixed-width types to preserve determinism.
 */
using digits_t = std::vector<unsigned int>;

auto convert(std::uint32_t in_base, const digits_t& digits, std::uint32_t out_base) -> digits_t;


}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
