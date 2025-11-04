#pragma once

#include <array>
#include <cstdint>

namespace yacht {

using DieValue = std::uint8_t;
using DiceArray = std::array<DieValue, 5>;

enum Category {
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

std::uint32_t score(const DiceArray& dice, const char* category);

}  // namespace yacht
