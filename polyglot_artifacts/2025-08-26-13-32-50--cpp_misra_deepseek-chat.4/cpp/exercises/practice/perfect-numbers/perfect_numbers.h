#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <stdexcept>
#include <cstdint>

namespace perfect_numbers {

enum class classification {
    perfect,
    abundant,
    deficient
};

classification classify(std::int32_t num);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
