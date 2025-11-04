#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

/* MISRA C++: fixed-width types are used to avoid implementation-defined widths. */
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

/*  Calculate the score for a given roll and category.
 *  The size of the dice array is fixed at compilation time, ensuring no dynamic allocation. */
[[nodiscard]] auto score(const std::array<std::uint8_t, 5U> & dice,
                         const Category                       category) -> std::uint32_t;

/* Convenience overload expected by the test-suite: accept the category as a
 * string (e.g. "yacht", "full house"). */
[[nodiscard]] auto score(const std::array<std::uint8_t, 5U> & dice,
                         std::string_view                      category) -> std::uint32_t;

} // namespace yacht
