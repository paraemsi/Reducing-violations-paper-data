#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

using u8 = std::uint8_t;
using i64 = std::int64_t;

enum class classification : u8
{
    perfect,
    abundant,
    deficient
};

classification classify(i64 n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
