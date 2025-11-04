#pragma once

#include <array>
#include <cstdint>
#include <vector>
#include <string_view>
#include <type_traits>
#include <initializer_list>

namespace yacht {

/* Enumeration of the available Yacht scoring categories.
 * The explicit underlying type keeps us within the fixed-width
 * integer domain required by the guidelines. */
enum class category : std::uint8_t {
    ones = 0U,
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

/* Calculate the Yacht score for a given list of five dice and a
 * scoring category.  The dice vector must contain exactly five
 * elements whose values are in the range [1, 6].
 *
 * Any deviation from the category’s pattern results in a score of 0. */
auto score(const std::vector<std::uint8_t>& dice, category cat) -> std::uint32_t;
auto score(const std::vector<std::uint8_t>& dice, std::string_view cat) -> std::uint32_t;

/* Generic wrapper to support client code that supplies the dice
 * as a vector of any integral type (e.g. std::vector<int>).  The
 * template is defined inline so the compiler can instantiate it
 * for the required element type without violating the fixed-width
 * integer rules in our main implementation. */
template <typename IntegralT,
          typename = std::enable_if_t<std::is_integral_v<IntegralT> &&
                                      !std::is_same_v<IntegralT, std::uint8_t>>>
inline auto score(const std::vector<IntegralT>& dice, category cat) -> std::uint32_t
{
    std::vector<std::uint8_t> converted{};
    converted.reserve(dice.size());
    for (const IntegralT value : dice) {
        /* The Exercism test suite guarantees values 1-6, therefore the
         * narrowing cast is well-defined and loss-free. */
        converted.push_back(static_cast<std::uint8_t>(value));
    }
    return yacht::score(converted, cat);
}

/* Overloads that accept a brace-enclosed list of dice values so test
 * code can call yacht::score({1,2,3,4,5}, "choice") directly. */
template <typename IntegralT,
          typename = std::enable_if_t<std::is_integral_v<IntegralT>>>
inline auto score(std::initializer_list<IntegralT> dice, category cat) -> std::uint32_t
{
    const std::vector<IntegralT> vec{dice};
    return yacht::score(vec, cat);
}

template <typename IntegralT,
          typename = std::enable_if_t<std::is_integral_v<IntegralT>>>
inline auto score(std::initializer_list<IntegralT> dice, std::string_view cat) -> std::uint32_t
{
    const std::vector<IntegralT> vec{dice};
    return yacht::score(vec, cat);
}

template <typename IntegralT,
          typename = std::enable_if_t<std::is_integral_v<IntegralT> &&
                                      !std::is_same_v<IntegralT, std::uint8_t>>>
inline auto score(const std::vector<IntegralT>& dice, std::string_view cat) -> std::uint32_t
{
    std::vector<std::uint8_t> converted{};
    converted.reserve(dice.size());
    for (const IntegralT value : dice) {
        converted.push_back(static_cast<std::uint8_t>(value));
    }
    return yacht::score(converted, cat);
}

}  // namespace yacht
