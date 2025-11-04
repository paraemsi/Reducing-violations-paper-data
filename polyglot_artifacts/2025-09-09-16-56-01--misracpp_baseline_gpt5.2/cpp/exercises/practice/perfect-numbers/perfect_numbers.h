#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

namespace perfect_numbers {

#ifdef classification
#pragma push_macro("classification")
#undef classification
#endif
enum class classification { perfect, abundant, deficient };
#ifdef classification
#pragma pop_macro("classification")
#endif

classification classify(int n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
