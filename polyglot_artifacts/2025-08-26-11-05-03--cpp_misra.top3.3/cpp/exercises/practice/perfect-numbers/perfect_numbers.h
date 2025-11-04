#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>
#include <string>

namespace perfect_numbers {

typedef std::uint32_t number_t;

// Use lower-case enum name and values for test compatibility
enum classification {
    perfect,
    abundant,
    deficient
};

classification classify(number_t n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
