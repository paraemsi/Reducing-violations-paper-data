#pragma once
#include <cstdint>
#include <vector>
#include <string>

namespace yacht {

enum class Category {
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

std::int32_t score(const std::vector<std::int32_t>& dice, const std::string& category);

}  // namespace yacht
