#pragma once

#include <array>
#include <cstdint>
#include <string_view>
#include <initializer_list>

namespace yacht {

enum class Category : std::uint8_t {
    Ones,
    Twos,
    Threes,
    Fours,
    Fives,
    Sixes,
    FullHouse,
    FourOfAKind,
    LittleStraight,
    BigStraight,
    Choice,
    Yacht
};

/*  Calculate the score for the supplied dice in the given category.
 *  The dice array must contain exactly five elements with values in the range 1..6.
 */
auto score(Category category, std::array<std::uint8_t, 5U> const& dice) -> std::uint32_t;
auto score(std::array<std::uint8_t, 5U> const& dice, std::string_view category) -> std::uint32_t;
auto score(std::initializer_list<std::uint8_t> dice, std::string_view category) -> std::uint32_t;

}  // namespace yacht
