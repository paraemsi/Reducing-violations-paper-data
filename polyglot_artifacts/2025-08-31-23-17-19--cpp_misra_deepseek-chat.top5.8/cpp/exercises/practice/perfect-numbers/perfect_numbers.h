#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

using number_t = std::int64_t;

enum class classification {
    perfect,
    abundant,
    deficient
};

classification classify(number_t number);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
