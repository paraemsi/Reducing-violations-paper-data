#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

/* Enumeration of the available scoring categories */
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

/* Calculate the score for a given dice set and category */
auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t;
auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view cat) -> std::uint32_t;

}  // namespace yacht
