#pragma once

#include <cstdint>
#include <vector>

namespace yacht {

enum class category : std::uint8_t {
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

std::uint16_t score(const std::vector<std::uint8_t>& dice, category cat);
std::uint16_t score(const std::vector<std::uint8_t>& dice, const char* cat);

}  // namespace yacht
