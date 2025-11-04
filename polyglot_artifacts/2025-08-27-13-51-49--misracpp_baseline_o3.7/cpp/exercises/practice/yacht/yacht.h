#pragma once

#include <vector>
#include <string>

namespace yacht {

 // Scoring categories as defined by the game rules
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

/**
 * Calculate the Yacht score for a set of five dice in the given category.
 *
 * @param dice      A collection of exactly five integers, each in the range [1,6].
 * @param category  The scoring category to evaluate.
 * @return          The score obtained for the supplied dice in the chosen category.
 */
int score(const std::vector<int>& dice, Category category);
int score(const std::vector<int>& dice, const std::string& category);
inline int score(const std::vector<int>& dice, const char* category) {
    return score(dice, std::string{category});
}

}  // namespace yacht
