#pragma once

#include <array>
#include <cstdint>
#include <string_view>
#include <initializer_list>

namespace yacht {

using die_input_t = std::int32_t;

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
 * Compute the score for a Yacht dice hand.
 * `dice`  : exactly five dice values in the range 1-6 (inclusive).
 * `cat`   : the scoring category to evaluate.
 *
 * Returns the calculated score or 0U if the dice do not satisfy `cat`.
 */
auto score(const std::array<std::uint8_t, 5U>& dice,
           std::string_view                             cat) -> std::uint32_t;

/* Convenience overload so callers can pass a braced-list like
 * `{1, 2, 3, 4, 5}` without constructing `std::array` explicitly. */
auto score(std::initializer_list<die_input_t> dice, std::string_view cat)
    -> std::uint32_t;

}  // namespace yacht
