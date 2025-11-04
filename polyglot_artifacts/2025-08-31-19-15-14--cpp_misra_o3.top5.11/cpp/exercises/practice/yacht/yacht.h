#pragma once

#include <array>
#include <cstdint>
#include <string_view>
#include <cstddef>
#include <type_traits>

namespace yacht {

enum class Category : std::uint8_t {
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

auto score(const std::array<std::uint8_t, 5U>& dice, Category category) -> std::uint32_t;
auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view category) -> std::uint32_t;


template<typename T,
         typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, std::uint8_t>>>
inline auto score(const std::array<T, 5U>& dice, Category category) -> std::uint32_t
{
    std::array<std::uint8_t, 5U> converted {};
    for (std::size_t i {0U}; i < static_cast<std::size_t>(5U); ++i) {
        converted[i] = static_cast<std::uint8_t>(dice[i]);
    }
    return score(converted, category);
}

template<typename T,
         typename = std::enable_if_t<!std::is_same_v<std::decay_t<T>, std::uint8_t>>>
inline auto score(const std::array<T, 5U>& dice, std::string_view category) -> std::uint32_t
{
    std::array<std::uint8_t, 5U> converted {};
    for (std::size_t i {0U}; i < static_cast<std::size_t>(5U); ++i) {
        converted[i] = static_cast<std::uint8_t>(dice[i]);
    }
    return score(converted, category);
}

}  // namespace yacht
