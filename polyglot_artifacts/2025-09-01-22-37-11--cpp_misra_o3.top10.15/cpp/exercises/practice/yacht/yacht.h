#pragma once

#include <array>
#include <cstdint>
#include <cstddef>
#include <string_view>

namespace yacht {

/* Yacht scoring categories */
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

/* Convenience alias for the 5-dice hand */
using dice_array = std::array<std::uint8_t, 5U>;

/* Calculate the score for the given dice in the requested category */
[[nodiscard]] auto score(dice_array dice, category cat) -> std::int32_t;
[[nodiscard]] auto score(dice_array dice, std::string_view cat) -> std::int32_t;

}  // namespace yacht
