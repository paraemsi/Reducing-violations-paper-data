#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

enum class classification : std::uint8_t
{
    perfect,
    abundant,
    deficient
};

using number_t = std::int64_t;

classification classify(number_t n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
