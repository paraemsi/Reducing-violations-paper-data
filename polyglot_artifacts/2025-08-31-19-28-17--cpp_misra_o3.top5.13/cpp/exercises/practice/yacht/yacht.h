#pragma once

#include <array>
#include <cstdint>
#include <string_view>

namespace yacht {

/* Enumeration of the available scoring categories.  The values are ordered so
 * that casting to an unsigned integer and adding one yields the face value
 * for the “ones … sixes” categories. */
enum class Category : std::uint8_t {
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

/* Calculate the Yacht score for the given set of dice in the selected
 * category.  The dice values must be in the range 1 – 6. */
auto score(const std::array<std::uint8_t, 5U>& dice, Category category) -> std::uint32_t;
auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view category_name) -> std::uint32_t;

}  // namespace yacht
