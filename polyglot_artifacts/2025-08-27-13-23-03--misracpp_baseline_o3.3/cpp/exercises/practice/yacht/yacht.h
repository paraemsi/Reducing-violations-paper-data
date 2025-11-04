#pragma once

#include <vector>
#include <string>

namespace yacht {

/// Categories used for scoring (matching exercism test names).
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

// Calculate the Yacht score for the given set of five dice in the
// specified category.
//
// `dice` must contain exactly five integers whose values are in the
// interval [1, 6].  If the dice do not fulfil the requirements of the
// requested category the function returns 0.
//
// Example:
//     score({3,3,3,5,5}, Category::FullHouse) == 19
int score(const std::vector<int>& dice, Category category);
int score(const std::vector<int>& dice, const std::string& category);

}  // namespace yacht
