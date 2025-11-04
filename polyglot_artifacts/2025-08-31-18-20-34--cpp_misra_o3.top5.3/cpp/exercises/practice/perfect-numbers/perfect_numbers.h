#ifndef PERFECT_NUMBERS_H
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

enum class classification : std::uint8_t {
    perfect,
    abundant,
    deficient
};

[[nodiscard]] auto classify(std::uint32_t value) -> classification;
[[nodiscard]] auto classify(std::int32_t value) -> classification;

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
