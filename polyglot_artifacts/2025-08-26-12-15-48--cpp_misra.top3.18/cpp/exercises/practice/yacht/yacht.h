#pragma once

#include <array>
#include <cstdint>

namespace yacht {

using Die = std::uint8_t;
using Dice = std::array<Die, 5U>;

enum class Category : std::uint8_t {
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

std::uint32_t score(const Dice& dice, Category category);
std::uint32_t score(const Dice& dice, const char* category_name);

}  // namespace yacht
