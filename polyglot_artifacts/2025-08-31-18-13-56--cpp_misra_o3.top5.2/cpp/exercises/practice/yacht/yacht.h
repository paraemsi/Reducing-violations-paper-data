#pragma once
#include <cstdint>
#include <array>
#include <vector>
#include <string>

namespace yacht {

/* Enumeration of the possible scoring categories */
enum class category : std::uint8_t
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

/* Calculate the score of the given dice for the supplied category */
using dice_vector = std::vector<std::uint8_t>;

/* Calculate the score of the given dice for the supplied category */
auto score(dice_vector const& dice, category cat) -> std::uint32_t;
auto score(dice_vector const& dice, std::string const& category_name) -> std::uint32_t;
auto score(dice_vector const& dice, char const* category_name) -> std::uint32_t;

}  // namespace yacht
