#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

/*  Nicomachus classification of natural numbers                                     */
enum class classification : std::uint8_t
{
    perfect,
    abundant,
    deficient
};

/*  Return the Nicomachus classification of `number`.                                */
auto classify(std::int32_t number) -> classification;

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
