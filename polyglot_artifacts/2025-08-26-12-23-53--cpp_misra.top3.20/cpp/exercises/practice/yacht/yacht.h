#pragma once

#include <array>
#include <cstdint>

namespace yacht {

using DieValue = std::uint8_t;
using DiceArray = std::array<DieValue, 5U>;

// MISRA: Use underlying type for enum class, but do not use std::uint8_t directly in code except here.
enum class Category : std::uint8_t {
    Ones = 0,
    Twos,
    Threes,
    Fours,
    Fives,
    Sixes,
    FullHouse,
    FourOfAKind,
    LittleStraight,
    BigStraight,
    Choice,
    Yacht
};

// MISRA: Use std::uint32_t for score return type.
std::uint32_t score(const DiceArray& dice, Category category);
std::uint32_t score(const DiceArray& dice, const char* category);

} // namespace yacht
