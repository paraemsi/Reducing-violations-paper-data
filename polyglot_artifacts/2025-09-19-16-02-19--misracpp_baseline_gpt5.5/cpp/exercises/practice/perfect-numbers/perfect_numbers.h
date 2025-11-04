#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

namespace perfect_numbers {

 // Nicomachus classification for positive integers by aliquot sum
#ifdef classification
#undef classification
#endif
enum class classification { perfect, abundant, deficient };

classification classify(int n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
