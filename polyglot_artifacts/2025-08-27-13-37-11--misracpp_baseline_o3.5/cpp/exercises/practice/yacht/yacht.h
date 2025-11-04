#pragma once

#include <vector>
#include <string_view>

namespace yacht {

enum class Category {
    Ones = 1,
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

/*
 * Calculate the yacht score for a given set of five dice in the supplied
 * category.
 *
 * dice     – exactly five integers whose values are in the range [1, 6]
 * category – one of the scoring categories defined above
 *
 * Returns the number of points earned for this throw.
 */
int score(const std::vector<int>& dice, Category category);
int score(const std::vector<int>& dice, std::string_view category);

}  // namespace yacht
