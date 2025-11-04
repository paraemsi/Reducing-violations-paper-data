#pragma once
#include <vector>

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

} // namespace yacht

Category yacht::category_from_string(const std::string& name);
int yacht::score(const std::vector<int>& dice, const std::string& category);
int yacht::score(const std::vector<int>& dice, Category category);
