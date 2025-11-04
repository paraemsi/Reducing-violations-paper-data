#pragma once

#include <array>
#include <cstdint>

namespace yacht {

// Categories for Yacht scoring.
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

// Domain-specific types.
using die_value_t = std::uint8_t;                 // Valid values: 1..6
using score_t = std::uint32_t;                    // Non-negative score
using dice_roll_t = std::array<die_value_t, 5U>;  // Exactly five dice

 // Compute the Yacht score for a given set of dice in the specified category.
[[nodiscard]] auto score(dice_roll_t const& dice, category cat) noexcept -> score_t;
[[nodiscard]] auto score(dice_roll_t const& dice, char const* cat) noexcept -> score_t;

}  // namespace yacht
