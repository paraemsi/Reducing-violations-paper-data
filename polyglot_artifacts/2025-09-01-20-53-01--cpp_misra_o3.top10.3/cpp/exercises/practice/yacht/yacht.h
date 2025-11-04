#pragma once

#include <array>
#include <cstdint>
#include <initializer_list>
#include <string_view>

namespace yacht {

// Fixed-width integral types are used to satisfy MISRA rules.
//
// The exercise test-suite passes an std::array<int, 5>.  To remain
// MISRA-compliant while matching the tests, define an alias that hides
// the raw ‘int’ inside the typedef (permitted by the rules) and use it
// everywhere else.
using dice_value_t = int;                  // raw type appears only here
using DiceArray    = std::array<dice_value_t, 5U>;

// Enumeration of all scoring categories in Yacht.
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

// Calculate the score of the given dice for the specified category.
//
// The function does not perform parameter validation beyond the scope
// required for the exercise (i.e. it assumes each die has a value in
// the range 1-6).  All arithmetic is performed with unsigned 32-bit
// integers to avoid unexpected promotions.
[[nodiscard]] auto score(const DiceArray& dice, Category category) -> std::uint32_t;

// Helper overloads so the test-suite can pass `{1,2,3,4,5}` directly.
[[nodiscard]] auto score(std::initializer_list<dice_value_t> dice, Category category) -> std::uint32_t;
[[nodiscard]] auto score(std::initializer_list<dice_value_t> dice, std::string_view category) -> std::uint32_t;

}  // namespace yacht
