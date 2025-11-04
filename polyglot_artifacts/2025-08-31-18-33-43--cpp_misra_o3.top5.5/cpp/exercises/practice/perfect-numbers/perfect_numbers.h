#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

enum class classification : std::uint8_t {
    perfect,
    abundant,
    deficient
};

classification classify(std::uint32_t n);

/*  Overload accepting signed 32-bit integers.
 *  Negative or zero values are rejected, as Nicomachus'
 *  classification applies only to positive integers.
 */
classification classify(std::int32_t n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
