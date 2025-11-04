#pragma once

#include <array>
#include <cstdint>
#include <string_view>
#include <type_traits>

namespace yacht {

using die_t   = std::uint8_t;
using score_t = std::uint32_t;

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

[[nodiscard]] score_t score(const std::array<die_t, 5U>& dice, category cat);

template <typename T,
          typename = std::enable_if_t<std::is_integral_v<T>>>
[[nodiscard]] score_t score(const std::array<T, 5U>& dice, category cat);

[[nodiscard]] score_t score(const std::array<die_t, 5U>& dice, std::string_view category_name);

template <typename T,
          typename = std::enable_if_t<std::is_integral_v<T>>>
[[nodiscard]] score_t score(const std::array<T, 5U>& dice, std::string_view category_name);

template <typename T, typename>
inline score_t score(const std::array<T, 5U>& dice, category cat)
{
    std::array<die_t, 5U> converted {};
    for (std::size_t i = 0U; i < 5U; ++i) {
        const T val = dice[i];
        if ((val < static_cast<T>(1)) || (val > static_cast<T>(6))) {
            return static_cast<score_t>(0U);
        }
        converted[i] = static_cast<die_t>(val);
    }
    return score(converted, cat);
}

template <typename T, typename>
inline score_t score(const std::array<T, 5U>& dice, std::string_view category_name)
{
    std::array<die_t, 5U> converted {};
    for (std::size_t i = 0U; i < 5U; ++i) {
        const T val = dice[i];
        if ((val < static_cast<T>(1)) || (val > static_cast<T>(6))) {
            return static_cast<score_t>(0U);
        }
        converted[i] = static_cast<die_t>(val);
    }
    return score(converted, category_name);
}

}  // namespace yacht
