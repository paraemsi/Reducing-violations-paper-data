#pragma once

#include <array>
#include <vector>
#include <cstdint>
#include <string_view>

namespace yacht {

/* Enumeration of scoring categories */
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

/* Type aliases used throughout the implementation */
using die_value_t = std::uint8_t;      /* dice values are 1-6, 8-bit is sufficient */
using score_t     = std::uint32_t;

/* Calculate the Yacht score for five dice in the given category */
auto score(const std::vector<die_value_t>& dice, category cat) -> score_t;
auto score(const std::vector<die_value_t>& dice, std::string_view cat) -> score_t;

}  // namespace yacht
