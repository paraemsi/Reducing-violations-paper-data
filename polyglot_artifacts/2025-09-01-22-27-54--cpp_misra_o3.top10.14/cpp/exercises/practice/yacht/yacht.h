#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

// Fixed set of scoring categories for the Yacht dice game
enum class category : std::uint8_t
{
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

// Calculate the score obtained by rolling `dice` in the given `cat`
auto score(const std::array<std::uint8_t, 5>& dice, category cat) -> std::uint32_t;

// Overload accepting the category as a textual name (used by the unit tests)
auto score(const std::array<std::uint8_t, 5>& dice, std::string_view cat_name) -> std::uint32_t;

}  // namespace yacht
