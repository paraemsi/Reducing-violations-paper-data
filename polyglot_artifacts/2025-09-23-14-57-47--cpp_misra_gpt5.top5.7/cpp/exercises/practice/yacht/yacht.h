#pragma once

#include <cstdint>
#include <initializer_list>
#include <vector>

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

auto score(const std::vector<std::int32_t>& dice, const char* cat) -> std::int32_t;
auto score(const std::vector<std::int32_t>& dice, category cat) -> std::int32_t;
auto score(std::initializer_list<std::int32_t> dice, const char* cat) -> std::int32_t;
auto score(std::initializer_list<std::int32_t> dice, category cat) -> std::int32_t;

}  // namespace yacht
