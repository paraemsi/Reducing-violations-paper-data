#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

/* Enumeration of all possible Yacht scoring categories */
enum class category
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

/* A fixed container for the five dice rolled in a single turn */
using dice_set = std::array<std::uint8_t, 5U>;

/* Compute the score obtained by `dice` when evaluated in `cat` */
[[nodiscard]] auto score(const dice_set& dice, category cat) -> std::uint32_t;
[[nodiscard]] auto score(const dice_set& dice, std::string_view cat) -> std::uint32_t;

}  /* namespace yacht */
