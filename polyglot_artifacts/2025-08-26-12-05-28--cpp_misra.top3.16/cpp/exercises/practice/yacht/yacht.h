#pragma once

#include <array>
#include <cstdint>

namespace yacht {

using DieValue = std::uint8_t;
using DiceArray = std::array<DieValue, 5>;

enum class Category : std::uint8_t
{
    Ones,
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

std::uint32_t score(const DiceArray& dice, Category category);
std::uint32_t score(const DiceArray& dice, const char* category_name);

}  // namespace yacht
