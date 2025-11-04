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
 * Calculate the score for a given dice roll in the supplied category.
 *
 * @param cat   The scoring category.
 * @param dice  A collection of exactly five dice with values 1-6.
 * @return      The score for the roll in the requested category.
 */
int score(category cat, const std::vector<int>& dice);

/**
 * Overload accepting dice first and a category name as string, matching test-suite
 * order and spelling.
 */
int score(const std::vector<int>& dice, const std::string& category_name);

}  // namespace yacht
