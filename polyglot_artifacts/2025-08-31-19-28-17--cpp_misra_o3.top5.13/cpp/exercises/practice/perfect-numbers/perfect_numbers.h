#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

/* Classification of a positive integer according to
 * Nicomachus' categories.
 */
enum class classification : std::uint8_t
{
    perfect = 0U,
    abundant = 1U,
    deficient = 2U
};

/* Return the classification of the given positive integer.
 * Throws std::domain_error if n is zero.
 */
auto classify(std::uint32_t n) -> classification;

}   // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
