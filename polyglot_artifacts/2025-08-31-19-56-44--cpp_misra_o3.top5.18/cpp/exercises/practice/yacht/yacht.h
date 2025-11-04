#pragma once

#include <array>
#include <cstdint>
#include <cstddef>
#include <string_view>

namespace yacht {

/* Game scoring categories */
enum class category : std::uint8_t {
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

auto score(const std::array<std::uint8_t, 5U>& dice, category cat) -> std::uint32_t;
auto score(const std::array<std::uint8_t, 5U>& dice, std::string_view cat_str) -> std::uint32_t;

/* Generic overloads – accept any integral dice element type */
template <typename T>
auto score(const std::array<T, 5U>& dice, category cat) -> std::uint32_t
{
    static_assert(std::is_integral_v<T>, "Dice value type must be integral");

    std::array<std::uint8_t, 5U> converted{};
    for (std::size_t i{0U}; i < 5U; ++i)
    {
        /* Explicit cast required – values limited to 1..6 by problem statement */
        converted[i] = static_cast<std::uint8_t>(dice[i]);
    }
    return score(converted, cat);
}

template <typename T>
auto score(const std::array<T, 5U>& dice, std::string_view cat_str) -> std::uint32_t
{
    static_assert(std::is_integral_v<T>, "Dice value type must be integral");

    std::array<std::uint8_t, 5U> converted{};
    for (std::size_t i{0U}; i < 5U; ++i)
    {
        converted[i] = static_cast<std::uint8_t>(dice[i]);
    }
    return score(converted, cat_str);
}

}  // namespace yacht
