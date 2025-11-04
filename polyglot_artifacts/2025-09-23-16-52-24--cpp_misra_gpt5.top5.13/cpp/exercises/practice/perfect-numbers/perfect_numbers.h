#ifndef PERFECT_NUMBERS_H
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

enum class classification : std::uint8_t
{
    perfect = 0U,
    abundant = 1U,
    deficient = 2U
};

classification classify(std::int64_t n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
