#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

/*
 * Classification of a positive integer according to Nicomachus.
 */
enum class classification
{
    perfect,
    abundant,
    deficient
};

/*
 * classify
 * Return the Classification of the supplied positive integer.
 *
 * The behaviour is undefined for n == 0 (problem domain: positive integers).
 */
[[nodiscard]] auto classify(std::uint32_t n) noexcept -> classification;

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
