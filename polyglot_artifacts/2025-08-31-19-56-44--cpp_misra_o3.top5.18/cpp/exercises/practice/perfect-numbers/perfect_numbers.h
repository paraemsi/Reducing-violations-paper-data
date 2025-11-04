#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

//--------------------------------------------------------------------------
//  Nicomachus classification of a positive integer based on its aliquot sum
//--------------------------------------------------------------------------
enum class classification
{
    perfect,
    abundant,
    deficient
};

//--------------------------------------------------------------------------
//  classify : Return the Nicomachus classification for the supplied value
//  PRECONDITION : value > 0 – behaviour is undefined for 0
//--------------------------------------------------------------------------
auto classify(std::int32_t value) -> classification;

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
