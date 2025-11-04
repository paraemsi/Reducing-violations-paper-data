#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers
{
    enum class classification
    {
        perfect,
        abundant,
        deficient
    };

    /*  Public API: determine the classification of an integer.
        For non-positive inputs, the function throws std::domain_error. */
    auto classify(std::int32_t value) -> classification;
} // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
