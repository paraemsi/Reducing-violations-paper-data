#pragma once

#include <array>
#include <cstdint>
#include <vector>
#include <string_view>

namespace yacht {

/* Fixed-width type aliases to satisfy MISRA C++ rules */
using DieValue = std::uint8_t;     /* dice show values 1-6             */
using Score    = std::uint32_t;    /* maximum score is below 2^32      */

/* Enumeration of the available scoring categories */
enum class Category
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

/*---------------------------------------------------------------------------*/
/*  Calculate the Yacht score for a roll of five dice in the given category  */
/*---------------------------------------------------------------------------*/
auto score(const std::array<DieValue, 5U>& dice, Category category) -> Score;
auto score(const std::vector<int>& dice, Category category) -> Score;

/* Overloads that accept the category as a text string (used by tests) */
auto score(const std::array<DieValue, 5U>& dice, std::string_view category) -> Score;
auto score(const std::vector<int>& dice, std::string_view category) -> Score;

/* Helper overloads for string literals used in tests */
inline auto score(const std::array<DieValue, 5U>& dice, const char* category) -> Score
{
    return score(dice, std::string_view{category});
}
inline auto score(const std::vector<int>& dice, const char* category) -> Score
{
    return score(dice, std::string_view{category});
}

}  // namespace yacht
