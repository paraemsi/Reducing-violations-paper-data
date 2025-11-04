#pragma once

#include <vector>
#include <string>

namespace yacht {

/**
 * Enumeration of the available Yacht scoring categories.
 */
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

/**
 * Calculate the score for a given roll of five dice in the specified category.
 *
 * @param dice     A container of exactly five integers, each in the range [1, 6].
 * @param category The scoring category to evaluate.
 * @return         The score as defined by the Yacht rules.
 */
int score(const std::vector<int>& dice, Category category);

/**
 * Convenience overload that accepts the category as a string literal.
 * Comparison is case-insensitive and understands phrases used in the
 * Exercism tests (e.g. "full house", "four of a kind").
 *
 * Any unrecognised string scores 0.
 */
int score(const std::vector<int>& dice, const std::string& category);

}  // namespace yacht
