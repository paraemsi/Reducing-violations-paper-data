#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

// Categories for scoring, matching the problem statement
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

// Fixed-width container for the five dice
using dice_array = std::array<std::uint8_t, 5U>;

// Calculate the Yacht score for a given set of dice and category.
auto score(dice_array const& dice, category cat) -> std::int32_t;
auto score(dice_array const& dice, std::string_view cat) -> std::int32_t;
auto score(dice_array const& dice, char const* cat) -> std::int32_t;

}  // namespace yacht
