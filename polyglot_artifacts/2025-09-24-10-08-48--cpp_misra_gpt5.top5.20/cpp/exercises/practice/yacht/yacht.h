#pragma once

#include <array>
#include <cstdint>
#include <cstddef>
#include <string_view>
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

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint16_t;
auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view cat) -> std::uint16_t;
auto score(const std::array<std::uint8_t, 5U>& dice, const char* cat) -> std::uint16_t;

// Overloads to accept test-friendly integer lists without narrowing issues
auto score(std::initializer_list<std::int32_t> dice, std::string_view cat) -> std::uint16_t;
auto score(std::initializer_list<std::int32_t> dice, const char* cat) -> std::uint16_t;

}  // namespace yacht
