#ifndef PERFECT_NUMBERS_H
#define PERFECT_NUMBERS_H
#include <cstdint>

namespace perfect_numbers {

enum class classification { perfect, abundant, deficient };

classification classify(int64_t n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
