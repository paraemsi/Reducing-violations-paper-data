#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

namespace perfect_numbers {

// Undefine any macros that might clash with our enum value names.
// Some testing or system headers occasionally define these words.
#if defined(perfect)
#undef perfect
#endif
#if defined(abundant)
#undef abundant
#endif
#if defined(deficient)
#undef deficient
#endif

enum class classification { perfect, abundant, deficient };

classification classify(int number);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
