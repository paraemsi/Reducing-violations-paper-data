#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

// Fixed-width alias for score values
using score_t = std::uint32_t;

// All possible scoring categories for Yacht
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

// Compute the score for a given set of five dice in the specified category
auto score(const std::array<std::uint8_t, 5U>& dice,
           category cat) noexcept -> score_t;

auto score(const std::array<std::uint8_t, 5U>& dice,
           std::string_view cat) noexcept -> score_t;

}  // namespace yacht
