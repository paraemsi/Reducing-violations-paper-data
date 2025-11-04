#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

using integer_t = std::int64_t;

enum class classification : std::uint8_t
{
    perfect = 0U,
    abundant = 1U,
    deficient = 2U
};

[[nodiscard]] auto classify(integer_t n) -> classification;

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
