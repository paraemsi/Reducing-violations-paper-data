#ifndef PERFECT_NUMBERS_H
#define PERFECT_NUMBERS_H

#include <cstdint>
#include <stdexcept>

namespace perfect_numbers {

using number_t = std::uint32_t;

enum class classification
{
    perfect,
    abundant,
    deficient
};

classification classify(number_t n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
