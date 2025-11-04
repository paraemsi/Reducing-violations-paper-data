#pragma once

#include <array>
#include <cstdint>
#include <string_view>

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

/**
 * \brief Calculate the Yacht score for a given set of dice and category.
 * \param dice     Array with exactly five dice values in the range [1,6].
 * \param cat      Scoring category.
 * \return         Calculated score, or zero when the dice do not satisfy the
 *                 requirements of the chosen category.
 */
auto score(const std::array<std::int32_t, 5U>& dice, category cat) -> std::int32_t;
auto score(const std::array<std::int32_t, 5U>& dice, std::string_view cat) -> std::int32_t;

}  // namespace yacht
