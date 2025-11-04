#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers
{
enum class classification
{
    perfect,
    abundant,
    deficient
};

using integer_t = std::int32_t;
using uinteger_t = std::uint32_t;

[[nodiscard]] auto classify(integer_t number) -> classification;
}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
