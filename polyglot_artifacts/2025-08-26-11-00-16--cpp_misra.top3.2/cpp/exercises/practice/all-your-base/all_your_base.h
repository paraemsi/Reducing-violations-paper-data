#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

typedef std::uint32_t Digit;
typedef std::vector<Digit> Digits;

Digits convert(std::uint32_t from_base, const Digits& in_digits, std::uint32_t to_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
