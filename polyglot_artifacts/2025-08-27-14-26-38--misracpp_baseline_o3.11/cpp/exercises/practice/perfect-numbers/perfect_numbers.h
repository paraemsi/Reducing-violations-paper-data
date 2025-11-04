#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <stdexcept>

namespace perfect_numbers {

enum class classification {
    perfect,
    abundant,
    deficient
};

/**
 * Classify a positive integer as perfect, abundant, or deficient.
 *
 * @param n A positive integer to classify.
 * @return The classification enum value.
 * @throws std::domain_error if n <= 0.
 */
classification classify(int n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
