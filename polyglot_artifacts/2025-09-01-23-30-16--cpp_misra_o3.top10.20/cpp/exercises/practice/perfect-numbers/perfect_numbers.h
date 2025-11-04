#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers
{

enum class Classification : std::uint8_t
{
    perfect,
    abundant,
    deficient
};
using classification = Classification;

/* Determine whether a positive integer is perfect, abundant, or deficient.
 * \param number  The positive integer to classify (must be > 0).
 * \return        The corresponding Classification value.
 * \exception     std::invalid_argument if number is 0.
 */
auto classify(std::uint32_t number) -> Classification;

} // namespace perfect_numbers

#endif // PERFECT_NUMBERS_H
