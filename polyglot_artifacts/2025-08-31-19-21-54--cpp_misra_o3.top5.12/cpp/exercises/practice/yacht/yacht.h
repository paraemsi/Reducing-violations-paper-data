#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

//  The twelve possible scoring categories
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

//  Type aliases – keep raw fundamental types localised
using die_t   = std::uint8_t;
using dice_t  = std::array<die_t, 5U>;
using score_t = std::uint32_t;

//  Calculate the score that the supplied dice obtain in the given category
auto score(dice_t const& dice, category cat) -> score_t;
auto score(dice_t const& dice, std::string_view name) -> score_t;

}  // namespace yacht
