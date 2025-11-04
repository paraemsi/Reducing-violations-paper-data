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

/*
 * Calculate the score for a given roll in the specified category.
 *
 * Parameters:
 *  - c:     the scoring category
 *  - dice:  exactly five integers in the inclusive range [1,6]
 *
 * Returns:
 *  - the integer score according to Yacht rules
 */
int score(category c, const std::vector<int>& dice);
int score(const std::vector<int>& dice, const std::string& category);

}  // namespace yacht
