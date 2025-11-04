#pragma once
#include <array>
#include <cstdint>
#include <cstddef>

namespace yacht {

/* Yacht scoring categories */
enum class category : std::uint8_t {
    ones             = 1U,
    twos             = 2U,
    threes           = 3U,
    fours            = 4U,
    fives            = 5U,
    sixes            = 6U,
    full_house       = 7U,
    four_of_a_kind   = 8U,
    little_straight  = 9U,
    big_straight     = 10U,
    choice           = 11U,
    yacht            = 12U
};

/* Convenient alias for the 5-dice hand */
using dice_array = std::array<std::uint8_t, 5U>;

/* Compute the score for the given hand/category (enum version) */
[[nodiscard]] auto score(const dice_array& dice, const category cat) -> std::uint32_t;

/* Convenience overload that accepts a C-string category name.
 * It maps the textual name used in the unit-tests to the strongly-typed enum
 * and then delegates to the main implementation above. */
[[nodiscard]] auto score(const dice_array& dice, const char* cat) -> std::uint32_t;

/* Overloads that accept the int-typed std::array the tests create via
 * list-initialisation and forward to the strongly-typed implementation. */
[[nodiscard]] auto score(const std::array<int, 5>& dice, const category cat) -> std::uint32_t;
[[nodiscard]] auto score(const std::array<int, 5>& dice, const char*     cat) -> std::uint32_t;

}  // namespace yacht
