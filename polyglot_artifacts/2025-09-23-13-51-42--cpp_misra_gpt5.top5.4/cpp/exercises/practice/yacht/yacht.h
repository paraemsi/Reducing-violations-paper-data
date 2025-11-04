#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace yacht {

enum class category : std::uint8_t {
    ones = 0U,
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

using die_value_t = std::uint8_t;
using score_t = std::int32_t;
using dice_roll = std::array<die_value_t, 5U>;

[[nodiscard]] auto score(dice_roll const& dice, category cat) noexcept -> score_t;
[[nodiscard]] auto score(dice_roll const& dice, char const* cat) noexcept -> score_t;

}  // namespace yacht
