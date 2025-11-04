#pragma once

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

Category category_from_string(const std::string& name);

int score(const std::vector<int>& dice, const std::string& category);

int score(const std::vector<int>& dice, Category category);

}  // namespace yacht
