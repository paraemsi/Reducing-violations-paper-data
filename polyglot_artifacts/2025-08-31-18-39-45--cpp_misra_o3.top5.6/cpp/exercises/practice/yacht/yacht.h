#pragma once

#include <array>
#include <cstdint>
#include <cstddef>
#include <string_view>

namespace yacht {

/*
 * Enumeration of the scoring categories described by the Yacht rules.
 */
enum class category
{
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

/*  Type aliases used throughout the implementation – keep raw
 *  fundamental types confined to these definitions to respect MISRA.
 */
using die_value_t = std::uint8_t;
using score_t     = std::uint32_t;

/*
 * Calculate the score for a roll of five dice given a scoring category.
 */
[[nodiscard]] auto score(std::array<die_value_t, 5U> const& dice, category cat) -> score_t;
[[nodiscard]] auto score(std::array<die_value_t, 5U> const& dice, std::string_view cat_name) -> score_t;

}  // namespace yacht
