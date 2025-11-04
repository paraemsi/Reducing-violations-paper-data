#pragma once

#include <array>
#include <cstdint>

namespace yacht {

 // Categories for Yacht scoring.
enum class category : std::uint8_t {
    ones = 1,
    twos = 2,
    threes = 3,
    fours = 4,
    fives = 5,
    sixes = 6,
    full_house = 7,
    four_of_a_kind = 8,
    little_straight = 9,
    big_straight = 10,
    choice = 11,
    yacht = 12
};

// Compute the Yacht score for five dice in the given category.
auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t;
// Overload accepting a C-string category name used by tests.
auto score(const std::array<std::uint8_t, 5U>& dice, const char* cat) -> std::uint32_t;

}  // namespace yacht
