#pragma once

#include <vector>
#include <cstdint>
#include <string_view>

namespace yacht {

/* Fixed-width aliases for clarity and MISRA compliance */
using dice_value_t = std::uint32_t;
using score_t      = std::uint32_t;

/* Enumeration of all scoring categories */
enum class Category : std::uint8_t
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

/* Calculate the score of a Yacht roll for the given category */
auto score(const std::vector<dice_value_t>& dice, Category category) -> score_t;
auto score(const std::vector<dice_value_t>& dice, std::string_view category) -> score_t;

}  // namespace yacht
