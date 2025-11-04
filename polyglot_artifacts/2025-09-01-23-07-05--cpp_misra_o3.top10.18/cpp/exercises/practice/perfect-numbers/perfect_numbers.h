#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers
{

enum class classification
{
    perfect,
    abundant,
    deficient
};

using uint64 = std::uint64_t;

auto classify(uint64 n) -> classification;

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
