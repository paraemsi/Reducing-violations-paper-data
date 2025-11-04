#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

/*
 * Enumeration of all scoring categories for the Yacht game.
 * The explicit underlying type is std::uint8_t to avoid using the
 * implementation-defined standard integer types (MISRA rule).
 */
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

/*
 * Compute the Yacht score for a fixed set of five dice and a category.
 *
 * dice  : exactly five values in the range [1,6]
 * cat   : scoring category
 * return: score according to the official Yacht rules
 */
auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t;
auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view category_name)
    -> std::uint32_t;

}  // namespace yacht
