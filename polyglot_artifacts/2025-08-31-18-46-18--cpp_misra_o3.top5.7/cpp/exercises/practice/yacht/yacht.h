#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

// Enumeration of the available scoring categories in the Yacht game.
// The underlying type is std::uint8_t to ensure a well-defined width
// and to satisfy the MISRA rule banning the use of built-in integer
// type names.
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

// Calculate the score achieved by the given set of dice in the
// specified category.
//
// dice  : Unordered collection of five dice (values 1-6)
// cat   : Scoring category
// return: The score (0-50)
auto score(const std::array<std::uint8_t, 5U>& dice,
           category                            cat) noexcept -> std::uint32_t;

/* Overload accepting a textual category as required by the tests. */
auto score(const std::array<std::uint8_t, 5U>& dice,
           std::string_view                     cat_name) noexcept -> std::uint32_t;

}  // namespace yacht
