#pragma once

#include <array>
#include <cstdint>
#include <cstddef>
#include <string_view>
#include <type_traits>

namespace yacht {

/* Enumeration of the available scoring categories in Yacht */
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

/*  Calculate the score for the given dice roll and category.
 *  dice:     exactly five dice values in the inclusive range [1, 6]
 *  category: one of the enumerated scoring categories
 *  returns:  the score as an unsigned 32-bit integer
 */
auto score(const std::array<std::uint8_t, 5U>& dice,
           const Category                       category) -> std::uint32_t;

/* Convenience overload that accepts the category as text, exactly matching
 * the strings used by the unit-tests (e.g. "yacht", "full house").
 */
auto score(const std::array<std::uint8_t, 5U>& dice,
           std::string_view                     category) -> std::uint32_t;

/* Convenience overload for raw C-strings coming from the tests */
inline auto score(const std::array<std::uint8_t, 5U>& dice,
                  const char*                         category) -> std::uint32_t
{
    return score(dice, std::string_view{category});
}

/* ------------------------------------------------------------------ */
/* Template helpers so tests can pass a std::array of *any* integral  */
/* type deduced from `{1,2,3,4,5}`.  Values are safely converted to   */
/* std::uint8_t and forwarded to the main implementation.             */
/* ------------------------------------------------------------------ */
template <typename T>
inline auto score(const std::array<T, 5U>& dice,
                  const std::string_view   category) -> std::uint32_t
{
    static_assert(std::is_integral_v<T>,
                  "dice element type must be an integral type");

    std::array<std::uint8_t, 5U> converted{};
    for (std::size_t i = 0U; i < 5U; ++i) {
        converted[i] = static_cast<std::uint8_t>(dice[i]);
    }
    return score(converted, category);
}

template <typename T>
inline auto score(const std::array<T, 5U>& dice,
                  const char*              category) -> std::uint32_t
{
    return score(dice, std::string_view{category});
}

}  // namespace yacht
