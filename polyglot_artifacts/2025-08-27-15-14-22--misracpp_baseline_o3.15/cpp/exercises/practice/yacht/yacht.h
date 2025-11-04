#pragma once

#include <array>
#include <cstdint>
#include <vector>
#include <string>

namespace yacht {

// Categories available in the Yacht game.
enum class Category : std::uint8_t {
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

// Compute the score obtained by the given set of dice in the specified
// category.
// `dice` must contain exactly 5 integers in the range [1, 6].
// Any invalid input is considered undefined behaviour.
int score(const std::vector<int>& dice, Category category);
int score(const std::vector<int>& dice, const std::string& category_str);

}  // namespace yacht
