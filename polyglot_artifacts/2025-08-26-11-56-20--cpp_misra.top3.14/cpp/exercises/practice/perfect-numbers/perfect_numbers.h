#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>
#include <string>

namespace perfect_numbers {

using number_t = std::uint32_t;

// Use lower-case enum name and values for test compatibility
enum classification {
    perfect,
    abundant,
    deficient
};

classification classify(number_t n);

std::string to_string(classification c);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
