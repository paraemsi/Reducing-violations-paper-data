#pragma once

#include <array>
#include <cstdint>

namespace yacht {

using DieValue = std::uint8_t;
using Dice = std::array<DieValue, 5U>;

 // MISRA C++: Use explicit underlying type for enum class and avoid direct use of std types in interface
// Category enum class for scoring categories
enum class Category : std::uint8_t
{
    Ones = 0U,
    Twos = 1U,
    Threes = 2U,
    Fours = 3U,
    Fives = 4U,
    Sixes = 5U,
    FullHouse = 6U,
    FourOfAKind = 7U,
    LittleStraight = 8U,
    BigStraight = 9U,
    Choice = 10U,
    Yacht = 11U
};

// MISRA C++: Provide an alias for the return type to avoid direct use of std types in interface
using ScoreType = std::uint32_t;

ScoreType score(const Dice& dice, Category category);
ScoreType score(const Dice& dice, const char* category);

}  // namespace yacht
