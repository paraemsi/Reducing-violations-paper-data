#pragma once

#include <array>
#include <cstdint>
#include <string_view>
#include <initializer_list>

namespace yacht {

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

/**
 * \brief Calculate the Yacht score for a given set of dice and scoring category.
 *
 * \param cat      The scoring category to evaluate.
 * \param dice     Five dice, each having a face value in the range [1, 6].
 * \return         The score obtained for the supplied dice in the chosen category.
 */
auto score(Category cat, const std::array<std::uint8_t, 5U>& dice) -> std::int32_t;
auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view category) -> std::int32_t;

/* Convenience overload used by the unit-tests – allows
 * passing dice as a braced-initializer list. */
template <typename IntegerT>
auto score(std::initializer_list<IntegerT> dice, std::string_view category) -> std::int32_t;

}  // namespace yacht
