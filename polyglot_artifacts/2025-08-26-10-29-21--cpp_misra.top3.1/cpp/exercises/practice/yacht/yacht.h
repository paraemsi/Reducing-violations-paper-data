#pragma once

#include <array>
#include <cstdint>

namespace yacht {

/*
 * Use a type alias for dice values and score, as per MISRA C++ rules.
 * These aliases are for clarity and to avoid direct use of std types in user code.
 */
typedef std::uint8_t dice_value_t;
typedef std::uint16_t score_t;

/* The number of dice in a Yacht game. */
#define YACHT_NUM_DICE (5U)

/* The available scoring categories. */
enum category_t
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

/* Convert a string to a category_t. Returns true if successful, false otherwise. */
bool category_from_string(const char* str, category_t& out_category);

/* Calculate the score for a given set of dice and a category. */
score_t score(const std::array<dice_value_t, YACHT_NUM_DICE>& dice, category_t category);

/* Overload: Calculate the score for a given set of dice and a category name as string. */
score_t score(const std::array<dice_value_t, YACHT_NUM_DICE>& dice, const char* category_name);

}  // namespace yacht
