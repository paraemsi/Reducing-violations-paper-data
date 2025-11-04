#ifndef PERFECT_NUMBERS_H
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

enum class Classification : std::uint8_t
{
    perfect,
    abundant,
    deficient
};

using classification = Classification;

auto classify(std::uint32_t n) -> Classification;

}   // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
