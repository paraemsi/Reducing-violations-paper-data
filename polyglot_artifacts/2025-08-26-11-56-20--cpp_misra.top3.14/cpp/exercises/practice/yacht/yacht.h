#pragma once

#include <array>
#include <cstdint>

namespace yacht {

typedef std::uint8_t DieValue;
typedef std::array<DieValue, 5U> DiceArray;

enum class Category : std::uint8_t {
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

std::uint32_t score(const DiceArray& dice, Category category);
std::uint32_t score(const DiceArray& dice, const char* category_name);

}  // namespace yacht
