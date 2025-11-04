#pragma once

#include <cstdint>
#include <array>
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

std::int32_t score(const std::array<std::int32_t, 5> &dice, category cat);
std::int32_t score(const std::array<std::int32_t, 5> &dice, const std::string &cat_name);

}  // namespace yacht
