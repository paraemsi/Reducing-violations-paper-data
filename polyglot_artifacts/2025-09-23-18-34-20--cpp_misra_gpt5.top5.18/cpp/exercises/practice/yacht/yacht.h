#pragma once

#include <array>
#include <vector>
#include <cstdint>
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

auto score(std::array<std::uint8_t, 5U> const& dice, category const cat) -> std::uint32_t;
auto score(std::vector<std::uint32_t> const& dice, category const cat) -> std::uint32_t;
auto score(std::vector<std::uint8_t> const& dice, category const cat) -> std::uint32_t;
auto score(std::vector<std::uint32_t> const& dice, char const* cat) -> std::uint32_t;
auto score(std::array<std::uint8_t, 5U> const& dice, char const* cat) -> std::uint32_t;
auto score(std::initializer_list<std::uint32_t> dice, char const* cat) -> std::uint32_t;

}  // namespace yacht
