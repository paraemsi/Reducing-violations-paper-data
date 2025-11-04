#ifndef PERFECT_NUMBERS_H
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

enum class classification : std::uint8_t
{
    perfect,
    abundant,
    deficient
};

[[nodiscard]] classification classify(std::int64_t value);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
