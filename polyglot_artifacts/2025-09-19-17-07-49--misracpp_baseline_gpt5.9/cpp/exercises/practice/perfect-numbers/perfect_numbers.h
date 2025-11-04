#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#if defined(__has_cpp_attribute)
  #if __has_cpp_attribute(nodiscard)
    #define PERFECT_NODISCARD [[nodiscard]]
  #else
    #define PERFECT_NODISCARD
  #endif
#else
  #define PERFECT_NODISCARD
#endif

namespace perfect_numbers {

enum class classification { perfect, abundant, deficient };

PERFECT_NODISCARD classification classify(int n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
