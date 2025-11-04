#pragma once

#include <vector>
#include <string>

namespace yacht {

// Scoring categories for the Yacht dice game
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

// Compute the score for a given set of dice under the specified category.
// Expects five dice values in the range [1, 6], but will safely handle any input.
int score(const std::vector<int>& dice, category cat);
int score(const std::vector<int>& dice, const std::string& cat);

}  // namespace yacht
