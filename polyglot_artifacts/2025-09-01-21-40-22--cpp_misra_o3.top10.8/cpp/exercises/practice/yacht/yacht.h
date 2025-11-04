#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

using score_t = std::uint32_t;
using die_t   = std::uint8_t;
using hand_t  = std::array<die_t, 5U>;

enum class category : std::uint8_t {
    ones = 1U,
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

/*  Calculate the Yacht score for the supplied dice in the given category.
 *  The function adheres to the MISRA C++ rules requested.
 */
auto score(const hand_t& dice, std::string_view cat) -> score_t;

}  // namespace yacht
