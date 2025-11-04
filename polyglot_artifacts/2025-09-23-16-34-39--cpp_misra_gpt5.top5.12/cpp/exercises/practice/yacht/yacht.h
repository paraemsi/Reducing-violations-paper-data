#pragma once

#include <array>
#include <cstdint>
#include <cstddef>

namespace yacht {

using die_t = std::uint8_t;
using score_t = std::uint32_t;

enum class category : std::uint8_t
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

auto score(const std::array<die_t, 5U>& dice, category cat) noexcept -> score_t;
// Convenience overload for tests passing category as a string literal.
auto score(const std::array<die_t, 5U>& dice, const char* cat) noexcept -> score_t;

}  // namespace yacht
