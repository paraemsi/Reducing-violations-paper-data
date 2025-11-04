#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

enum class classification
{
    perfect,
    abundant,
    deficient
};

/*--------------------------------------------------------------------
 * @brief  Classify a positive integer as perfect, abundant, or deficient
 *
 * @param  number  The integer to be classified (must be > 0)
 * @return         The corresponding classification value
 *
 * @throws std::domain_error  If number is non-positive (≤ 0) because classification
 *                            is defined only for strictly positive integers
 *------------------------------------------------------------------*/
[[nodiscard]] auto classify(std::int32_t number) -> classification;

}   // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
