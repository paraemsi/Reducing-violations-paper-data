#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

using uint8  = std::uint8_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;
using int32  = std::int32_t;

enum class classification : uint8
{
    perfect,
    abundant,
    deficient
};

/*  Determine if a positive integer is perfect, abundant, or deficient
 *  \param number  Positive integer to classify
 *  \return        classification::perfect   when aliquot sum equals number
 *                 classification::abundant  when aliquot sum exceeds number
 *                 classification::deficient when aliquot sum is below number
 */
auto classify(int32 number) -> classification;

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
