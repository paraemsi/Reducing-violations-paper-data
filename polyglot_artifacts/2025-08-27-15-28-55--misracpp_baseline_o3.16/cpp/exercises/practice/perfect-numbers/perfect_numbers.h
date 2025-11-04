#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

namespace perfect_numbers {

// Some system headers (rarely) define `classification` as a macro.
// Undefining it here prevents pre-processor collisions with our enum name.
#ifdef classification
#undef classification
#endif

enum class classification { perfect, abundant, deficient };

classification classify(int n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
