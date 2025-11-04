#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <stdexcept>

namespace perfect_numbers {

enum class classification { perfect, abundant, deficient };

// Classify a positive integer according to Nicomachus' scheme.
// Throws std::domain_error when n is not a positive integer.
classification classify(int n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
