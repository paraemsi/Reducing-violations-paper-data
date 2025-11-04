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

// Calculate the score for a given set of five dice in the specified category.
int score(const std::vector<int>& dice, category cat);
int score(const std::vector<int>& dice, const std::string& cat);

}  // namespace yacht
