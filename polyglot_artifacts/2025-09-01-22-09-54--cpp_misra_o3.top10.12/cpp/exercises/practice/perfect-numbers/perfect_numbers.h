#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

enum class classification
{
    perfect,
    abundant,
    deficient
};

[[nodiscard]] auto classify(std::int32_t n) -> classification;

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
