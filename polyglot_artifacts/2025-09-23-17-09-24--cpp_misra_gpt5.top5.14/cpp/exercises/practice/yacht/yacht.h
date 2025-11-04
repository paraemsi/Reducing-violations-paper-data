#pragma once

#include <array>
#include <cstdint>
#include <cstddef>

namespace yacht {

using die_t = std::uint8_t;
using score_t = std::uint32_t;
constexpr std::size_t dice_count = static_cast<std::size_t>(5U);
using dice_t = std::array<die_t, dice_count>;

// Scoring categories for the Yacht game
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

// Calculate the score for the given dice and category
[[nodiscard]] auto score(dice_t const& dice, category cat) noexcept -> score_t;
// Overload that accepts a category by name (e.g., "yacht", "full house", ...)
[[nodiscard]] auto score(dice_t const& dice, char const* cat) noexcept -> score_t;

}  // namespace yacht
