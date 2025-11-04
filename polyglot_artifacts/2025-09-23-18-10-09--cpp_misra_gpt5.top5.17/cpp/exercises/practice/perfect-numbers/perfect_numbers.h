#if !defined(PERFECT_NUMBERS_H)
#define PERFECT_NUMBERS_H

#include <cstdint>

namespace perfect_numbers {

enum class classification : std::uint32_t
{
    perfect,
    abundant,
    deficient
};

classification classify(std::int64_t n);
classification classify(std::uint64_t n);

}  // namespace perfect_numbers

#endif  // PERFECT_NUMBERS_H
