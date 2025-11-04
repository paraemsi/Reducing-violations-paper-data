#ifndef PERFECT_NUMBERS_H
#define PERFECT_NUMBERS_H
#include <stdexcept>

namespace perfect_numbers {

enum class classification {
    perfect,
    abundant,
    deficient,
};

/**
 * Classify a positive integer as perfect, abundant, or deficient.
 *
 * @param n A positive integer to classify.
 * @return  The Classification enum value.
 *
 * @throws std::domain_error if n is not a positive integer.
 */
classification classify(int n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
