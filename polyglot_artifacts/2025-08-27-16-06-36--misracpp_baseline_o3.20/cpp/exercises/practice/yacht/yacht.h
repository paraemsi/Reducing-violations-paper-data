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
 * Calculate the score obtained for the given set of five dice when
 * applied to the provided scoring category.
 *
 * @param category The scoring category against which the dice are evaluated.
 * @param dice     A container with exactly five integers, each in the range [1,6].
 *
 * @return The score achieved for the specified category.
 */
int score(const std::vector<int>& dice, const std::string& category_name);

}  // namespace yacht
