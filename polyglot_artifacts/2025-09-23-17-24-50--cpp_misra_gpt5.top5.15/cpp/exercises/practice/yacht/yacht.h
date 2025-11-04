#pragma once

#include <array>
#include <cstdint>
#include <cstddef>
#include <initializer_list>

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

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t;
auto score(const std::array<std::uint8_t, 5U>& dice, const char* cat) -> std::uint32_t;
auto score(std::initializer_list<std::uint8_t> dice, const char* cat) -> std::uint32_t;

}  // namespace yacht
