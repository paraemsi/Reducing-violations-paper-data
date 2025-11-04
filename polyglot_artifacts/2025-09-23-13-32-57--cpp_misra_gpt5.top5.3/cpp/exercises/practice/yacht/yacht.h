#pragma once

#include <array>
#include <cstdint>

namespace yacht {

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

auto score(const std::array<std::int32_t, 5>& dice, category cat) noexcept -> std::int32_t;
auto score(const std::array<std::int32_t, 5>& dice, const char* cat) noexcept -> std::int32_t;

}  // namespace yacht
