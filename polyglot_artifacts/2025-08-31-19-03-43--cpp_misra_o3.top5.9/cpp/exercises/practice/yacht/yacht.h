#pragma once

#include <array>
#include <cstdint>
#include <cstddef>
#include <vector>
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

namespace detail {

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t;

}  // namespace detail

template<typename T>
auto score(const std::array<T, 5U>& dice, category cat) -> std::uint32_t
{
    std::array<std::uint8_t, 5U> converted{};
    for(std::size_t idx = 0U; idx < 5U; ++idx) {
        converted[idx] = static_cast<std::uint8_t>(dice[idx]);
    }
    return detail::score(converted, cat);
}

template<typename T>
auto score(const std::vector<T>& dice, category cat) -> std::uint32_t
{
    if(dice.size() != 5U) {
        return static_cast<std::uint32_t>(0U);
    }
    std::array<std::uint8_t, 5U> converted{};
    for(std::size_t idx = 0U; idx < 5U; ++idx) {
        converted[idx] = static_cast<std::uint8_t>(dice[idx]);
    }
    return detail::score(converted, cat);
}

auto score(std::initializer_list<int> dice, std::string_view cat) -> std::uint32_t;

}  // namespace yacht
