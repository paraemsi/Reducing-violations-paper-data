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
 * Calculate the score for the given dice roll in the specified category.
 *
 * @param dice A vector of exactly five integers, each between 1 and 6 (inclusive).
 * @param cat  The scoring category to use.
 * @return     The score obtained for the roll in the given category.
 */
int score(const std::vector<int>& dice, category cat);
int score(const std::vector<int>& dice, const std::string& category_str);
inline int score(const std::vector<int>& dice, const char* category_cstr) {
    return score(dice, std::string{category_cstr});
}

}  // namespace yacht
