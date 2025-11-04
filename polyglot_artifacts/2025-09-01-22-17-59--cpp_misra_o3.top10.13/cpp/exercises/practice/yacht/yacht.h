#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

/* Yacht scoring categories */
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

/* Calculate the score for a roll in the given category */
auto score(const std::array<std::uint8_t, 5U>& dice, Category category) -> std::uint32_t;
auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view category) -> std::uint32_t;

}  // namespace yacht
