#pragma once

#include <vector>
#include <string_view>

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

int score(const std::vector<int>& dice, category cat);
int score(const std::vector<int>& dice, std::string_view cat);

}  // namespace yacht
