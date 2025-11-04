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

int score(const std::vector<int>& dice, Category category);
Category category_from_string(const std::string& name);

}  // namespace yacht
