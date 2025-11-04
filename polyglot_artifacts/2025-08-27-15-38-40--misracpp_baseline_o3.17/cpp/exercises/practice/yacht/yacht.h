#pragma once

#include <vector>
#include <string>

namespace yacht {

enum class category {
    ones,
    twos,
    threes,
    fours,
    fives,
    sixes,
    full_house,
    four_of_a_kind,
    little_straight,
    big_straight,
    choice,
    yacht
};

/**
 * Calculate the score for a set of five dice in the given category.
 *
 * @param dice A collection of exactly five integers in the range [1, 6].
 * @param cat  The scoring category to evaluate.
 * @return The integer score obtained.
 */
int score(const std::vector<int>& dice, const std::string& cat);

}  // namespace yacht
