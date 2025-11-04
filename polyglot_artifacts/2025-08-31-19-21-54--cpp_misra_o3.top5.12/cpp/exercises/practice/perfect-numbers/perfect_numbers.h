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

auto classify(std::int32_t number) -> classification;

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
