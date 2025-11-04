#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {
    // Alias for unsigned integer type to comply with MISRA rules
    using number_t = std::uint32_t;
    
    enum class classification {
        perfect,
        abundant,
        deficient
    };
    
    classification classify(number_t num);
}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
