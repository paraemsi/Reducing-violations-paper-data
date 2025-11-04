#pragma once

#include <vector>
#include <string>

namespace yacht {

enum class Category {
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
 * Calculate the Yacht score for a given set of dice and scoring category.
 *
 * @param dice     A vector containing exactly five integers, each in the range 1-6.
 * @param category The scoring category to apply.
 * @return         The score for the supplied dice in the given category.
 */
int score(const std::vector<int>& dice, Category category);
int score(const std::vector<int>& dice, const std::string& category);
inline int score(const std::vector<int>& dice, const char* category_cstr) {
    // delegate literal / C-string calls to the std::string overload
    return category_cstr ? score(dice, std::string{category_cstr}) : 0;
}

}  // namespace yacht
