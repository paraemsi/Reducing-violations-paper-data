#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

enum class category : std::uint8_t {
    ones = 1U,
    twos = 2U,
    threes = 3U,
    fours = 4U,
    fives = 5U,
    sixes = 6U,
    full_house,
    four_of_a_kind,
    little_straight,
    big_straight,
    choice,
    yacht
};

[[nodiscard]] auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::int32_t;

/* Convenience overload used by the tests */
[[nodiscard]] auto score(const std::array<std::uint8_t, 5U>& dice,
                         std::string_view                cat_name) -> std::int32_t;

}  // namespace yacht
