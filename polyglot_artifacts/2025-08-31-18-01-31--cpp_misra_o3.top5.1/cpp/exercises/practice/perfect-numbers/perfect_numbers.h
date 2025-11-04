#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

enum class classification
{
    perfect,
    abundant,
    deficient
};

using int_type  = std::int64_t;   // signed 64-bit integer
using uint_type = std::uint64_t;  // unsigned 64-bit integer

[[nodiscard]] auto classify(int_type n) -> classification;

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
