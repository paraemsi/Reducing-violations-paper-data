#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>
#include <stdexcept>

#if defined(__has_cpp_attribute)
#  if __has_cpp_attribute(nodiscard) >= 201603
#    define PERF_NODISCARD [[nodiscard]]
#  else
#    define PERF_NODISCARD
#  endif
#else
#  define PERF_NODISCARD
#endif

namespace perfect_numbers {

enum class classification { perfect, abundant, deficient };

/*
 *  Classify a positive integer using Nicomachus' scheme.
 *
 *  @param n  Positive integer to classify.
 *  @return   classification::perfect   if n equals its aliquot sum
 *            classification::abundant  if n is less than its aliquot sum
 *            classification::deficient if n is greater than its aliquot sum
 *
 *  @throws std::domain_error if n <= 0
 */
PERF_NODISCARD classification classify(std::int64_t n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
