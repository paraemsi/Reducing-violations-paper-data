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

Category parse_category(const std::string& name);

int score(const std::vector<int>& dice, Category category);
int score(const std::vector<int>& dice, const std::string& category);

} // namespace yacht
