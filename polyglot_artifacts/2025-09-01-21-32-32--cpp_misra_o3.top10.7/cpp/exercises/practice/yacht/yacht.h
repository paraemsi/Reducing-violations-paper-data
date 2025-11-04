#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

/* Enumeration of the possible scoring categories in the Yacht dice game */
enum class category : std::uint8_t
{
    ones            = 1U,
    twos            = 2U,
    threes          = 3U,
    fours           = 4U,
    fives           = 5U,
    sixes           = 6U,
    full_house      = 7U,
    four_of_a_kind  = 8U,
    little_straight = 9U,
    big_straight    = 10U,
    choice          = 11U,
    yacht           = 12U
};

/*  Calculate the score for a set of five dice in the given category.
 *
 *  \param dice     An std::array holding exactly five dice values. Each value
 *                  shall be in the range 1-6 inclusive.
 *  \param cat      The scoring category to be evaluated.
 *  \return         The score obtained for the given dice and category.
 */
[[nodiscard]] auto score(const std::array<std::uint8_t, 5U>& dice,
                         category cat) -> std::uint32_t;

[[nodiscard]] auto score(const std::array<std::uint8_t, 5U>& dice,
                         std::string_view cat) -> std::uint32_t;

}  // namespace yacht
