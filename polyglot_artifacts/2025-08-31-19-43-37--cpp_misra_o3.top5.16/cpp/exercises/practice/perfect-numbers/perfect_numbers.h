#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

// Classification result
enum class classification { perfect, abundant, deficient };

// Alias to comply with MISRA C++: fixed-width type is wrapped once here
using integer = std::int32_t;

// Return the Nicomachus classification of the supplied positive integer.
// Throws std::domain_error when n <= 0.
classification classify(const integer n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
