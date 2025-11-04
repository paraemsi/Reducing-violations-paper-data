#pragma once

#include <array>
#include <cstdint>

namespace yacht {

typedef std::uint8_t DieValue;
typedef std::array<DieValue, 5> DiceArray;

enum Category : std::uint8_t {
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
Category category_from_string(const char* name);

}  // namespace yacht
