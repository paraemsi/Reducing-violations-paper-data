#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

enum class classification : std::uint8_t { perfect = 0, abundant = 1, deficient = 2 };

auto classify(std::int64_t value) -> classification;

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
