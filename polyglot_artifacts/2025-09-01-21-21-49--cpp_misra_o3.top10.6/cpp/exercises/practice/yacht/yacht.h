#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace yacht {

/* Enumeration of the available scoring categories in the Yacht game */
enum class category
{
    yacht,
    four_of_a_kind,
    full_house,
    little_straight,
    big_straight,
    choice,
    ones,
    twos,
    threes,
    fours,
    fives,
    sixes
};

/*  Calculate the score for a roll of five dice in a given category.
 *  @param dice         Five dice values (each in the range 1-6).
 *  @param category_str The scoring category to evaluate (free-form text from the test suite).
 *  @return             The score for the specified category; zero if the dice do not satisfy it.
 */
auto score(const std::vector<std::int32_t>& dice, const std::string& category_str) -> std::uint32_t;

}  // namespace yacht
