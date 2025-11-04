#ifndef YACHT_H
#define YACHT_H

#include <string_view>
#include <initializer_list>

namespace yacht {

// Scoring categories for the Yacht game.
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

// Calculate the score for the given roll of five dice in the specified category.
//
// Public interface – accepts the same brace-initialiser syntax used by the tests.
int score(std::initializer_list<int> dice, category cat);
int score(std::initializer_list<int> dice, std::string_view cat_name);

}  // namespace yacht

#endif  // YACHT_H
