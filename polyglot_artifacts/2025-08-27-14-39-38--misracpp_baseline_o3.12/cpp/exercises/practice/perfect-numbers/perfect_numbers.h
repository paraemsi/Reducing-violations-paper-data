#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

// Some system headers (e.g. Objective-C runtime) may define a `classification`
// macro that clashes with the enum name below.  Undefine it to avoid
// pre-processor substitution errors when this header is included after such
// headers.
#ifdef classification
#undef classification
#endif
// Guard against stray macros that may clash with our enumerator names.
#ifdef perfect
#undef perfect
#endif
#ifdef abundant
#undef abundant
#endif
#ifdef deficient
#undef deficient
#endif

namespace perfect_numbers {

enum class classification { perfect, abundant, deficient };

// Return the Nicomachus classification of a positive integer.
// Throws std::domain_error if n is not a positive integer.
classification classify(int n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
